/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:06:50 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/01 14:10:23 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				index;
	long long		last_eat;
	char			flag_eat;
	struct s_table	*table;
	pid_t			pid;
	pthread_t		check_death;
}	t_philo;

typedef struct s_table
{
	int				alive;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;
	sem_t			*forks;
	sem_t			*print_log;
	sem_t			*end;
	sem_t			*eat_block;
	t_philo			*philos;
	long long		start_time;
}	t_table;

int			ft_atoi(const char *str);
long long	get_time(void);
int			error(int err);
void		think(t_philo *philo, t_table *table);
void		eat(t_philo *philo, t_table *table);
void		take_forks(t_philo *philo, t_table *table);
void		philo_init(t_table *table, char **argv, int argc);
int			parent(t_philo *philo);
void		help_end(t_table *table, t_philo *philos);

#endif