/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:08:23 by rturker           #+#    #+#             */
/*   Updated: 2023/01/10 13:22:13 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					philo_number;
	int					p_eat_count;
	pthread_mutex_t		left_hand;
	pthread_mutex_t		*right_hand;
	long long			last_eat_time;
	struct s_data		*info;
	pthread_t			thread;
}	t_philo;

typedef struct s_data
{
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				check_eat;
	int				philo_count;
	long long		starttime;
	int				is_dead;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	print_life_mutex;
	t_philo			*philos;
}	t_data;

int			check_num(char **str);
void		*main_loop(void *item);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			init_data(t_data *data, char **av, int ac);
int			init_philos(t_data *data);
void		eating(t_philo *philo);
void		destroy_mutex(t_data *data);
int			thread_init(t_data *item);
void		is_died(t_data *data, t_philo *p);
void		sleep_control(long long time, t_data *data);
long long	current_timestamp(void);
int			argument_control(char **av);
void		life_print(t_data *data, int philo_num, char *state);
void		sleep_control(long long time, t_data *data);

#endif
