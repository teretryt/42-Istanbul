/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:10:46 by rturker           #+#    #+#             */
/*   Updated: 2023/01/19 11:23:18 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	main_loop(t_philo *philo)
{
	philo->last_eat_time = current_timestamp();
	pthread_create(&philo->info->data_thread, NULL, &is_died, philo);
	if (philo->philo_number % 2 == 0)
		usleep(10000);
	while (!(philo->info->is_dead))
	{
		eating(philo);
		if (philo->p_eat_count >= philo->info->must_eat
			&& philo->info->must_eat != -1)
			break ;
		life_print(philo->info, philo->philo_number - 1, "is sleeping");
		sleep_control(philo->info->sleep_time, philo->info);
		life_print(philo->info, philo->philo_number - 1, "is thinking");
	}
	pthread_join(philo->info->data_thread, NULL);
	if (philo->info->is_dead)
		exit(1);
	exit(0);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->info->forks);
	life_print(philo->info, philo->philo_number - 1, "has taken a fork");
	sem_wait(philo->info->forks);
	life_print(philo->info, philo->philo_number - 1, "has taken a fork");
	sem_wait(philo->info->eating_sem);
	life_print(philo->info, philo->philo_number - 1, "is eating");
	philo->last_eat_time = current_timestamp();
	sem_post(philo->info->eating_sem);
	sleep_control(philo->info->eat_time, philo->info);
	philo->p_eat_count++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	*is_died(void *item)
{
	t_philo	*p;
	t_data	*data;

	p = (t_philo *)item;
	data = p->info;
	while (1)
	{
		sem_wait(data->eating_sem);
		if (current_timestamp() - p->last_eat_time > (long)data->die_time)
		{
			life_print(data, p->philo_number - 1,
				"died");
			data->is_dead = 1;
			exit(1);
		}
		sem_post(data->eating_sem);
		if (data->is_dead)
			break ;
		if (p->p_eat_count >= p->info->must_eat && p->info->must_eat != -1)
			break ;
		usleep(1000);
	}
	return (NULL);
}
