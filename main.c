/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vess <vess@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 22:14:53 by vess              #+#    #+#             */
/*   Updated: 2022/05/02 22:38:35 by vess             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_philos(t_info *info)
{
	int			i;

	i = -1;
	while (++i < info->total)
	{
		info->philos[i].info = info;
		if (pthread_create(&info->philos[i].thread, NULL, philo, \
			&info->philos[i]))
			return (ft_error("Pthread did not return 0\n"));
	}
}

int	check_death2(t_info *info)
{
	pthread_mutex_lock(&info->dead);
	while (info->stop)
	{
		pthread_mutex_unlock(&info->dead);
		return (1);
	}
	pthread_mutex_unlock(&info->dead);
	return (0);
}

static void	join_and_free_philos(t_info *info)
{
	int	i;

	i = -1;
	while (check_death2(info))
		ft_usleep(1);
	while (++i < info->total)
		pthread_join(info->philos[i].thread, NULL);
	pthread_mutex_destroy(&info->write_mutex);
	i = -1;
	while (++i < info->total)
		pthread_mutex_destroy(&info->philos[i].left);
	if (info->stop == 2)
		printf("Each philosopher ate %d time(s)\n", info->m_eat);
	free(info->philos);
}

int	main(int ac, char **av)
{
	t_info	info;

	memset(&info, 0, sizeof(info));
	if (ac == 5 || ac == 6)
	{
		if (handle_args(ac, av, &info) != 0)
			return (ft_error("Error : invalid arguments"), 1);
	}
	else
		return (ft_error("Error : invalid arguments"), 1);
	create_philos(&info);
	join_and_free_philos(&info);
	return (0);
}
