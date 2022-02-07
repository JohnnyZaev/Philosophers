/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:06:15 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/01 14:13:55 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	he_live(t_philo *philo)
{
	size_t	i;
	int		must_eat;

	must_eat = philo->table->notepme;
	if (philo->alive == 0)
		return (0);
	else if (must_eat != -1 && philo->flag_eat >= must_eat)
		return (0);
	return (1);
}

static void	*philo_work(void *philo)
{
	t_philo	*philo_tmp;
	size_t	*i;

	philo_tmp = (t_philo *)philo;
	while (he_live(philo_tmp))
	{
		take_forks(philo_tmp);
		eat(philo_tmp);
		think(philo_tmp);
	}
	return (NULL);
}

static void	check_death(t_table *table)
{
	size_t		i;
	long long	time_to_die;
	t_philo		*philos;

	philos = table->philos;
	while (they_live(philos, table->number_of_philosophers))
	{
		i = 0;
		while (i < table->number_of_philosophers && \
			they_live(philos, table->number_of_philosophers))
		{
			time_to_die = get_time() - philos[i].last_eat;
			if (time_to_die > (int)table->time_to_die)
			{
				pthread_mutex_lock(&table->print_log);
				philos[i].alive = 0;
				printf("%lld %u is died\n", \
				get_time() - table->start_time, philos[i].index + 1);
				cleaner(table, 1);
				return ;
			}
			i++;
		}
	}
	cleaner(table, 0);
}

static void	philo_start(t_table *table)
{
	size_t	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->number_of_philosophers)
	{
		if (pthread_create(&(table->philosophers[i]), NULL, \
			&philo_work, &(table->philos[i])))
			error(3);
		i++;
		usleep(50);
	}
	check_death(table);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (error(1));
	philo_init(&table, argv, argc);
	philo_start(&table);
}
