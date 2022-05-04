/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vess <vess@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:55:22 by vess              #+#    #+#             */
/*   Updated: 2022/05/03 16:01:29 by vess             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define FT_ERROR		1
# define FT_SUCCESS		0

# define NOCOL "\033[0m"
# define RED "\033[1;31m"
# define YEL "\033[1;33m"
# define ORG "\033[0;33m"
# define GRN "\033[1;32m"
# define CIA "\033[1;36m"
# define DGRAY "\033[1;90m"
# define BLU "\033[1;34m"
# define MGN "\033[1;35m"

enum e_msg {
	MSG_FORK = 0,
	MSG_EAT,
	MSG_SLP,
	MSG_THK,
	MSG_RIP
};
/*-----Structure Philo--*/
typedef struct s_philo
{
	int				id; // id of the philosopher
	pthread_mutex_t	left;  // right fork mutex
	pthread_mutex_t	*right;  // left fork mutex
	pthread_t		thread;
	pthread_t		thread_death; 
	struct s_info	*info;
	long int		ms_eat;  // time of the last dinner in milliseconds 
	int				finish; // 1 when a philosopher ate m_eat times, if not, 0
	unsigned int	nb_eat;	// number of dinners (each time the philosopher eats nb_eat++)
}					t_philo;
/*-----Structure Table--*/
typedef struct s_info
{
	int				total; // number of philosophers
	int				die; // time to die in milliseconds
	int				eat; // time to eat in milliseconds
	int				sleep; // time to sleep in milliseconds
	int				m_eat; // must eat m_eat times
	t_philo			*philos;
	pthread_mutex_t	write_mutex; // write mutex
	pthread_mutex_t	dead; // write mutex
	pthread_mutex_t	time_eat;
	pthread_mutex_t	finish;
	int				nb_p_finish; // when a philosopher ate m_eat times : nb_p_finish++
	long int		start_t; // start time in milliseconds
	int				stop; // 0 if none philosopher is dead, 1 if a philosopher is dead, 2 if all philosophers ate m_eat times
}			t_info;
/*-------Parsing--------*/
void			ft_error(char *str);
int				ft_isdigit(int c);
int				ft_isnum(char *str);
int				ft_atoi(const char *str);
int				check_nbrs(int ac, char **av);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				check_args(int ac, char **av);
int				handle_args(int ac, char **av, t_info *table);
/*-------Threads--------*/
void			*philo(void *argv);
char			*get_clr(int msg);
char			*get_msg(int msg);
long int		get_time(void);
void			print_msg(t_philo *philo, int msg);
void			ft_usleep(long int ms);
int				check_death(t_philo *philo, int i);
#endif