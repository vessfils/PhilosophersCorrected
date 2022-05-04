/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vess <vess@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:54:43 by vess              #+#    #+#             */
/*   Updated: 2022/05/04 15:42:49 by vess             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
static void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right);
	else
		pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(&philo->info->write_mutex);
	print_msg(philo, MSG_FORK);
	pthread_mutex_unlock(&philo->info->write_mutex);
	if (!philo->right)
	{
		ft_usleep(philo->info->die * 2);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->left))
			pthread_mutex_unlock(philo->right);
		pthread_mutex_lock(&philo->info->write_mutex);
		print_msg(philo, MSG_FORK);
		pthread_mutex_unlock(&philo->info->write_mutex);
	}
	else
	{
		if (pthread_mutex_lock(philo->right))
			pthread_mutex_unlock(&philo->left);
		pthread_mutex_lock(&philo->info->write_mutex);
		print_msg(philo, MSG_FORK);
		pthread_mutex_unlock(&philo->info->write_mutex);
	}
}


void	activity(t_philo *philo)
{

	/*
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(&philo->info->write_mutex);
	print_msg(philo, MSG_FORK);
	pthread_mutex_unlock(&philo->info->write_mutex);
	if (!philo->right)
	{
		ft_usleep(philo->info->die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(&philo->info->write_mutex);
	print_msg(philo, MSG_FORK);
	pthread_mutex_unlock(&philo->info->write_mutex);
	*/
	take_fork(philo);
	pthread_mutex_lock(&philo->info->write_mutex);
	print_msg(philo, MSG_EAT);
	pthread_mutex_lock(&philo->info->time_eat);
	philo->ms_eat = get_time();
	pthread_mutex_unlock(&philo->info->time_eat);
	pthread_mutex_unlock(&philo->info->write_mutex);
	ft_usleep(philo->info->eat);
	if (philo->right)
		pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(&philo->left);
	sleep_think(philo);
}

void	*is_dead(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;

	ft_usleep(philo->info->die + 1);
	pthread_mutex_lock(&philo->info->time_eat);
	pthread_mutex_lock(&philo->info->finish);
	if (!check_death(philo, 0) && !philo->finish && \
		((get_time() - philo->ms_eat) >= (long)(philo->info->die)))
	{
		pthread_mutex_unlock(&philo->info->time_eat);
		pthread_mutex_unlock(&philo->info->finish);
		pthread_mutex_lock(&philo->info->write_mutex);
		print_msg(philo, MSG_RIP);
		pthread_mutex_unlock(&philo->info->write_mutex);
		check_death(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->time_eat);
	pthread_mutex_unlock(&philo->info->finish);
	return (NULL);
}

void	*philo(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	if ((philo->id % 2) == 0)
		ft_usleep(philo->info->eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death, NULL, is_dead, av);
		activity(philo);
		pthread_detach(philo->thread_death);
		if ((int)++philo->nb_eat == philo->info->m_eat)
		{
			pthread_mutex_lock(&philo->info->finish);
			philo->finish = 1;
			philo->info->nb_p_finish++;
			if (philo->info->nb_p_finish == philo->info->total)
			{
				pthread_mutex_unlock(&philo->info->finish);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->info->finish);
			return (0);
		}
	}
	return (NULL);
}
