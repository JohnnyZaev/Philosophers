/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:21:31 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/01 13:41:11 by gvarys           ###   ########.fr       */
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
	table->alive = 1;
}

static void	malloc_helper(t_table *table)
{
	table->philos = \
		malloc((sizeof(t_philo)) * table->number_of_philosophers);
	if (!table->philos)
		error(2);
	sem_unlink("/forks");
	sem_unlink("/logs");
	sem_unlink("/end");
	sem_unlink("/ttd");
	table->forks = \
		sem_open("/forks", O_CREAT | O_EXCL, \
		777, table->number_of_philosophers);
	table->print_log = \
		sem_open("/logs", O_CREAT | O_EXCL, 777, 1);
	table->end = \
		sem_open("/end", O_CREAT | O_EXCL, 777, 0);
	table->eat_block = \
		sem_open("/ttd", O_CREAT | O_EXCL, 777, 1);
	if (table->forks <= 0 || table->print_log <= 0 || \
		table->end <= 0 || table->eat_block <= 0)
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
		table->philos[i].index = i;
		table->philos[i].table = table;
		table->philos[i].last_eat = get_time();
		table->philos[i].flag_eat = 0;
		i++;
	}
}
