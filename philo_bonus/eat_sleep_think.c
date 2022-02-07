/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:11:28 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/01 14:14:40 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	help_end(t_table *table, t_philo *philos)
{
	sem_wait(table->print_log);
	table->alive = 0;
	printf("%lld %u is died\n", \
	get_time() - table->start_time, philos->index + 1);
	sem_post(table->end);
	exit(1);
}

static int	check_after_print(t_philo *philo)
{
	if (philo->flag_eat >= \
			philo->table->notepme \
			&& philo->table->notepme != -1)
	{
		sem_post(philo->table->end);
		return (1);
	}
	return (0);
}

void	take_forks(t_philo *philo, t_table *table)
{
	sem_wait(table->forks);
	sem_wait(table->print_log);
	printf("%lld %u has taken a fork\n", \
		get_time() - philo->table->start_time, philo->index + 1);
	if (!check_after_print(philo))
		sem_post(table->print_log);
	sem_wait(table->forks);
	sem_wait(table->print_log);
	printf("%lld %u has taken a fork\n", \
		get_time() - philo->table->start_time, philo->index + 1);
	if (!check_after_print(philo))
		sem_post(table->print_log);
}

void	eat(t_philo *philo, t_table *table)
{
	long long	time;

	sem_wait(table->print_log);
	printf("%lld %u is eating\n", get_time() - philo->table->start_time, \
		philo->index + 1);
	sem_wait(table->eat_block);
	philo->flag_eat++;
	philo->last_eat = get_time();
	if (!check_after_print(philo))
		sem_post(table->print_log);
	sem_post(table->eat_block);
	time = get_time();
	while (get_time() - time < philo->table->time_to_eat)
		usleep(500);
	sem_post(table->forks);
	sem_post(table->forks);
}

void	think(t_philo *philo, t_table *table)
{
	long long	time;

	sem_wait(table->print_log);
	printf("%lld %u is sleeping\n", get_time() - philo->table->start_time, \
		philo->index + 1);
	if (!check_after_print(philo))
		sem_post(table->print_log);
	time = get_time();
	while (get_time() - time < philo->table->time_to_sleep)
		usleep(500);
	sem_wait(table->print_log);
	printf("%lld %u is thinking\n", get_time() - philo->table->start_time, \
		philo->index + 1);
	if (!check_after_print(philo))
		sem_post(table->print_log);
	usleep(100);
}
