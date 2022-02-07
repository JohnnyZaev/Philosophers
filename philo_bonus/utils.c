/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:45:17 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/07 10:44:52 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_error(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res * sign) > 2147483647)
			print_error();
		if ((res * sign) < -2147483648)
			print_error();
	}
	return (res * sign);
}

long long	get_time(void)
{
	struct timeval	t;
	long long		time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1e3) + (t.tv_usec * 1e-3);
	return (time);
}

int	error(int err)
{
	if (err == 1)
		printf("Argument error\n");
	if (err == 2)
		printf("Malloc error\n");
	if (err == 3)
		printf("Pthread error\n");
	if (err == 4)
		printf("Semaphore error\n");
	if (err == 5)
		printf("Fork error\n");
	exit(err);
	return (0);
}

int	parent(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->table->number_of_philosophers)
		if (philo[i].pid == 0)
			return (0);
	return (1);
}
