/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vess <vess@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:56:40 by vess              #+#    #+#             */
/*   Updated: 2022/05/05 11:15:03 by vess             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

long int	get_time(void)
{
	struct timeval	current_time;
	long int		time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_usleep(long int ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < ms)
		usleep(ms / 10);
}

void	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->write_mutex);
	print_msg(philo, MSG_SLP);
	pthread_mutex_unlock(&philo->info->write_mutex);
	ft_usleep(philo->info->sleep);
	pthread_mutex_lock(&philo->info->write_mutex);
	print_msg(philo, MSG_THK);
	pthread_mutex_unlock(&philo->info->write_mutex);
}
