/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:21:31 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/01 15:26:02 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	help_init(t_table *table, char **argv, int argc)
{
	table->number_of_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		table->notepme = ft_atoi(argv[5]);
		if (table->notepme < 1)
			error(1);
	}
	else
		table->notepme = -1;
	if (table->number_of_philosophers < 1 || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1)
		error(1);
}

static void	malloc_helper(t_table *table)
{
	table->forks = NULL;
	table->philos = \
		malloc((sizeof(t_philo)) * table->number_of_philosophers);
	table->philosophers = \
		malloc(sizeof(pthread_t) * table->number_of_philosophers);
	table->forks = \
		malloc(sizeof(pthread_mutex_t) * table->number_of_philosophers);
	if (!table->philos || !table->philosophers || !table->forks)
		error(2);
	if (pthread_mutex_init(&table->print_log, NULL))
		error(4);
}

void	philo_init(t_table *table, char **argv, int argc)
{
	size_t	i;

	help_init(table, argv, argc);
	malloc_helper(table);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			error(4);
		i++;
	}
	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->philos[i].index = i;
		table->philos[i].table = table;
		table->philos[i].alive = 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = \
			&table->forks[(i + 1) % table->number_of_philosophers];
		table->philos[i].last_eat = get_time();
		table->philos[i].flag_eat = 0;
		i++;
	}
}
