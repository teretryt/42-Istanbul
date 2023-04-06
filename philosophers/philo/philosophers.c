/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:02:53 by rturker           #+#    #+#             */
/*   Updated: 2023/01/10 13:12:30 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, char **av, int ac)
{
	data->philo_count = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->is_dead = 0;
	data->check_eat = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (0);
	if (data->die_time < 0 || data->eat_time < 0)
		return (0);
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat <= 0)
			return (0);
	}
	else
		data->must_eat = -1;
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->eating_mutex, NULL);
	pthread_mutex_init(&data->print_life_mutex, NULL);
	while (++i < data->philo_count)
	{
		data->philos[i].p_eat_count = 0;
		data->philos[i].last_eat_time = 0;
		data->philos[i].info = data;
		data->philos[i].philo_number = i + 1;
		pthread_mutex_init(&(data->philos[i].left_hand), NULL);
		if (i == data->philo_count - 1)
			data->philos[i].right_hand = &(data->philos[0].left_hand);
		else
			data->philos[i].right_hand = &(data->philos[i + 1].left_hand);
	}
	return (1);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philos[i].thread, NULL);
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_destroy(&(data->philos[i].left_hand));
	pthread_mutex_destroy(&(data->eating_mutex));
	pthread_mutex_destroy(&(data->print_life_mutex));
}

int	thread_init(t_data *item)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)item;
	data->starttime = current_timestamp();
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&main_loop, &(data->philos[i])))
			return (0);
		data->philos[i].last_eat_time = current_timestamp();
		i++;
	}
	is_died(data, data->philos);
	destroy_mutex(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!argument_control(av))
			printf("Wrong Argument!\n");
		if (!init_data(&data, av, ac))
			return (-1);
		if (!init_philos(&data))
			return (-1);
		if (!thread_init(&data))
			return (-1);
	}
	else
		printf("Wrong Argument!\n");
}
