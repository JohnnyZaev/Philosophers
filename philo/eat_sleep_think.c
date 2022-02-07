/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:11:28 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/01 13:41:11 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_helper(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table->print_log);
	printf("%lld %u has taken a fork\n", \
		get_time() - philo->table->start_time, philo->index + 1);
	pthread_mutex_unlock(&philo->table->print_log);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->print_log);
	printf("%lld %u has taken a fork\n", \
		get_time() - philo->table->start_time, philo->index + 1);
	pthread_mutex_unlock(&philo->table->print_log);
}

void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
		fork_helper(philo);
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->table->print_log);
		printf("%lld %u has taken a fork\n", \
			get_time() - philo->table->start_time, philo->index + 1);
		pthread_mutex_unlock(&philo->table->print_log);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->table->print_log);
		printf("%lld %u has taken a fork\n", \
			get_time() - philo->table->start_time, philo->index + 1);
		pthread_mutex_unlock(&philo->table->print_log);
	}
}

void	eat(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->table->print_log);
	printf("%lld %u is eating\n", get_time() - philo->table->start_time, \
		philo->index + 1);
	philo->flag_eat++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->print_log);
	time = get_time();
	while (get_time() - time < philo->table->time_to_eat)
		usleep(500);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	think(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->table->print_log);
	printf("%lld %u is sleeping\n", get_time() - philo->table->start_time, \
		philo->index + 1);
	pthread_mutex_unlock(&philo->table->print_log);
	time = get_time();
	while (get_time() - time < philo->table->time_to_sleep)
		usleep(500);
	pthread_mutex_lock(&philo->table->print_log);
	printf("%lld %u is thinking\n", get_time() - philo->table->start_time, \
		philo->index + 1);
	pthread_mutex_unlock(&philo->table->print_log);
	usleep(100);
}

int	they_live(t_philo *philo, size_t number_of_philosophers)
{
	size_t	i;
	int		must_eat;

	i = 0;
	must_eat = philo[i].table->notepme;
	while (i < number_of_philosophers)
	{
		if (philo[i].alive == 0)
			return (0);
		else if (must_eat != -1 && philo->flag_eat >= must_eat)
			return (0);
		i++;
	}
	return (1);
}
