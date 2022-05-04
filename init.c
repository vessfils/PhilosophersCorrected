/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vess <vess@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 10:00:59 by vess              #+#    #+#             */
/*   Updated: 2022/05/03 15:31:34 by vess             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(t_info *info)
{
	pthread_mutex_init(&info->write_mutex, NULL);
	pthread_mutex_init(&info->dead, NULL);
	pthread_mutex_init(&info->time_eat, NULL);
	pthread_mutex_init(&info->finish, NULL);
}

static int	init(t_info *info)
{
	int	i;

	i = 0;
	info->start_t = get_time();
	info->stop = 0;
	info->nb_p_finish = 0;
	init_mutex(info);
	while (i < info->total)
	{
		info->philos[i].id = i + 1;
		info->philos[i].ms_eat = info->start_t;
		info->philos[i].nb_eat = 0;
		info->philos[i].finish = 0;
		info->philos[i].right = NULL;
		pthread_mutex_init(&info->philos[i].left, NULL);
		if (info->total == 1)
			return (1);
		if (i == info->total - 1)
			info->philos[i].right = &info->philos[0].left;
		else
			info->philos[i].right = &info->philos[i + 1].left;
		++i;
	}
	return (0);
}

static	int	check_info(t_info *info, int ac)
{
	if (ac == 6 && info->m_eat <= 0)
		return (ft_error("ERROR: wrong num of must eat\n"), 1);
	if (info->total < 0)
		return (ft_error("ERROR: wrong num of philo\n"), 1);
	if (info->die < 0)
		return (ft_error("ERROR: wrong time to die\n"), 1);
	if (info->eat < 0)
		return (ft_error("ERROR: wrong time to eat\n"), 1);
	if (info->sleep < 0)
		return (ft_error("ERROR: wrong time to sleep\n"), 1);
	return (FT_SUCCESS);
}

int	handle_args(int ac, char **av, t_info *tab)
{
	if (check_args(ac, av))
		return (1);
	tab->total = ft_atoi(av[1]);
	tab->die = ft_atoi(av[2]);
	tab->eat = ft_atoi(av[3]);
	tab->sleep = ft_atoi(av[4]);
	tab->m_eat = -1;
	if (ac == 6)
		tab->m_eat = ft_atoi(av[5]);
	check_info(tab, ac);
	tab->philos = (t_philo *)malloc(sizeof(t_philo) * tab->total);
	if (!tab->philos)
		return (ft_error("ERROR: malloc failed\n"), 1);
	init(tab);
	return (0);
}
