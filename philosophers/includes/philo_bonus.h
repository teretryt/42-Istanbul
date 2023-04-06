/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:08:23 by rturker           #+#    #+#             */
/*   Updated: 2023/01/13 11:12:17 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philo
{
	int					philo_number;
	int					p_eat_count;
	long long			last_eat_time;
	struct s_data		*info;
	pid_t				pid_no;
}	t_philo;

typedef struct s_data
{
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				philo_count;
	long long		starttime;
	int				is_dead;
	sem_t			*eating_sem;
	sem_t			*print_life_sem;
	sem_t			*forks;
	t_philo			*philos;
	pthread_t		data_thread;
}	t_data;

int			check_num(char **str);
void		main_loop(t_philo *philo);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			init_data(t_data *data, char **av, int ac);
int			init_philos(t_data *data);
void		eating(t_philo *philo);
void		destroy_sem(t_data *data);
int			init_proc(t_data *item);
void		*is_died(void *item);
void		sleep_control(long long time, t_data *data);
long long	current_timestamp(void);
int			argument_control(char **av);
void		life_print(t_data *data, int philo_num, char *state);
void		sleep_control(long long time, t_data *data);

#endif
