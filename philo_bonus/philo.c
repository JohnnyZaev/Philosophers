/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:06:15 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/01 14:10:30 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleaner(t_table *table, t_philo *philo)
{
	int	i;

	sem_wait(table->end);
	if (parent(philo))
	{
		i = -1;
		while (++i < table->number_of_philosophers)
			kill(philo[i].pid, SIGTERM);
		i = -1;
		while (++i < table->number_of_philosophers)
			waitpid(philo[i].pid, NULL, 0);
	}
	free(table->philos);
	sem_unlink("/forks");
	sem_close(table->forks);
	sem_unlink("/logs");
	sem_close(table->print_log);
	sem_unlink("/end");
	sem_close(table->end);
	sem_unlink("/ttd");
	sem_close(table->eat_block);
}

static void	philo_work(t_philo *philo, t_table *table)
{
	while (table->alive == 1)
	{
		take_forks(philo, table);
		eat(philo, table);
		if (philo->flag_eat >= \
			table->notepme && \
			table->notepme != -1)
			break ;
		think(philo, table);
	}
	exit(1);
}

static void	*check_death(void *philo_tmp)
{
	t_philo		*philos;
	t_table		*table;
	long long	time_to_die;

	philos = (t_philo *)philo_tmp;
	table = philos->table;
	while (table->alive != 0)
	{
		sem_wait(table->eat_block);
		time_to_die = get_time() - philos->last_eat;
		if (time_to_die > table->time_to_die)
			help_end(table, philos);
		sem_post(table->eat_block);
		if (philos->flag_eat >= philos->table->notepme \
			&& philos->table->notepme != -1)
			break ;
	}
	exit(1);
	return (NULL);
}

static void	philo_start(t_table *table)
{
	size_t	i;

	i = -1;
	table->start_time = get_time();
	while (++i < table->number_of_philosophers)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid < 0)
			error(4);
		if (table->philos[i].pid == 0)
		{
			if (pthread_create(&table->philos[i].check_death, \
				NULL, &check_death, &table->philos[i]))
				error(3);
			philo_work(&(table->philos[i]), table);
			break ;
		}
	}
	cleaner(table, table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (error(1));
	philo_init(&table, argv, argc);
	philo_start(&table);
	return (0);
}
