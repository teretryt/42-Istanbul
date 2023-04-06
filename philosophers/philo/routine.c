/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:10:46 by rturker           #+#    #+#             */
/*   Updated: 2023/01/19 12:28:12 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*main_loop(void *item)
{
	t_philo	*philo;

	philo = (t_philo *)item;
	if (philo->philo_number % 2 == 0)
		usleep(10000);
	while (!(philo->info->is_dead))
	{
		eating(philo);
		if (philo->info->check_eat)
			break ;
		life_print(philo->info, philo->philo_number - 1, "is sleeping");
		sleep_control(philo->info->sleep_time, philo->info);
		life_print(philo->info, philo->philo_number - 1, "is thinking");
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_hand));
	life_print(philo->info, philo->philo_number - 1, "has taken a fork");
	if (philo->info->philo_count == 1)
	{
		sleep_control(philo->info->die_time * 2, philo->info);
		pthread_mutex_unlock(&(philo->left_hand));
	}
	pthread_mutex_lock(philo->right_hand);
	life_print(philo->info, philo->philo_number - 1, "has taken a fork");
	pthread_mutex_lock(&(philo->info->eating_mutex));
	life_print(philo->info, philo->philo_number - 1, "is eating");
	philo->last_eat_time = current_timestamp();
	pthread_mutex_unlock(&(philo->info->eating_mutex));
	sleep_control(philo->info->eat_time, philo->info);
	philo->p_eat_count++;
	pthread_mutex_unlock(philo->right_hand);
	pthread_mutex_unlock(&(philo->left_hand));
}

void	is_died(t_data *data, t_philo *p)
{
	int	i;

	while (!(data->check_eat))
	{
		i = -1;
		while (++i < data->philo_count && !(data->is_dead))
		{
			pthread_mutex_lock(&(data->eating_mutex));
			if (current_timestamp() - p[i].last_eat_time > (long)data->die_time)
			{
				life_print(data, i, "died");
				data->is_dead = 1;
			}
			pthread_mutex_unlock(&(data->eating_mutex));
			usleep(100);
		}
		if (data->is_dead)
			break ;
		i = 0;
		while (data->must_eat != -1 && p[i].p_eat_count >= data->must_eat - 1
			&& i < data->philo_count)
			i++;
		if (i == data->philo_count)
			data->check_eat = 1;
	}
}
