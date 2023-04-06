/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:02:02 by rturker           #+#    #+#             */
/*   Updated: 2023/01/10 13:15:12 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	current_timestamp(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return (te. tv_sec * 1000 + te. tv_usec / 1000);
}

void	sleep_control(long long time, t_data *data)
{
	long long	i;

	i = current_timestamp();
	while (!(data->is_dead))
	{
		if ((current_timestamp() - i) >= time)
			break ;
		usleep(50);
	}
}
