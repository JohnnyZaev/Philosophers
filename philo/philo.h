/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:06:50 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/01 13:41:11 by gvarys           ###   ########.fr       */
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

typedef struct s_philo
{
	int				index;
	int				alive;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_eat;
	char			flag_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_log;
	t_philo			*philos;
	long long		start_time;
}	t_table;

int			ft_atoi(const char *str);
long long	get_time(void);
int			error(int err);
void		think(t_philo *philo);
void		eat(t_philo *philo);
void		take_forks(t_philo *philo);
int			they_live(t_philo *philo, size_t number_of_philosophers);
void		philo_init(t_table *table, char **argv, int argc);
void		cleaner(t_table *table, int flag);

#endif