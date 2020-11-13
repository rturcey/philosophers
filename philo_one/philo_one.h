/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:42:51 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 11:14:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

tableau de s_phi, 1 par philosophe avec des liens vers les forks et vers le print

typedef struct	s_phi
{
	int				nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_each;
	int				i;
	int				isdead;
	suseconds_t		origin;
	suseconds_t		time;
	suseconds_t		prev_meal;
	pthread_mutex_t	***forks;
	pthread_mutex_t	**print;
	
}				t_phi;

long long	ft_atoi(const char *str);
void		*print_str(char *str, int fd);
size_t		ft_strlen(char *str);
t_phi		*parse_argv(char **argv);
int			ft_isdigit(char c);
int			clear_mutex(t_phi *phi);
char		*ft_itoa(int n);
char		*ft_strjoin_sp(char *s1, char *s2);
char		*ft_strdup(const char *s1);

#endif