/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vess <vess@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:03:01 by vess              #+#    #+#             */
/*   Updated: 2022/05/03 16:08:14 by vess             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_clr(int msg)
{
	if (msg == MSG_FORK)
		return (YEL);
	if (msg == MSG_EAT)
		return (GRN);
	if (msg == MSG_SLP)
		return (BLU);
	if (msg == MSG_THK)
		return (CIA);
	if (msg == MSG_RIP)
		return (RED);
	return ("Error: not valid msg id");
}

char	*get_msg(int msg)
{
	if (msg == MSG_FORK)
		return ("(-3-) has taken a fork");
	if (msg == MSG_EAT)
		return ("(^o^) is eating");
	if (msg == MSG_SLP)
		return ("(u.u) is sleeping");
	if (msg == MSG_THK)
		return ("(7.7) is thinking");
	if (msg == MSG_RIP)
		return ("(x.x) died");
	return ("Error: not valid msg id");
}

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->info->dead);
	if (i)
		philo->info->stop = i;
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

void	print_msg(t_philo *philo, int msg)
{
	long int	time;

	time = -1;

	time = get_time() - philo->info->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(philo, 0))
	{
		printf(DGRAY"%ld ms", time);
		printf(MGN" %3d ", philo->id);
		printf("%s%s", get_clr(msg), get_msg(msg));
		printf("\n");
	}
}
