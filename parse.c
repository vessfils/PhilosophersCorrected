/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vess <vess@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:28:17 by vess              #+#    #+#             */
/*   Updated: 2022/05/01 10:01:30 by vess             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nbrs(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		if (av[i][0] == '-')
			return (1);
		else if (av[i][0] == '+')
			j++;
		if (!ft_isdigit(av[i][j + 1]))
			return (1);
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
		}
	}
	return (0);
}

int	check_int(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (*str == '+' && str++)
		len--;
	while (*str == '0' && *str & len--)
		str++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(str, "2147483648", 10) > 0)
		return (1);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (check_nbrs(ac, av))
		return (1);
	while (++i < ac)
	{
		if (check_int(av[i]))
			return (1);
	}
	return (0);
}
