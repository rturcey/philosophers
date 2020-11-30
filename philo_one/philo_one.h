/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:42:51 by user42            #+#    #+#             */
/*   Updated: 2020/11/30 10:48:46 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_phi
{
	int				nb;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				nb_each;
	int				i;
	time_t			origin;
	time_t			time;
	time_t			prev_meal;
	pthread_mutex_t	**forks;
	int				*try_forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*take;

}					t_phi;

int		g_isdead;

long long			ft_atoi(const char *str);
void				*print_str(char *str, int fd);
size_t				ft_strlen(char *str);
t_phi				**parse_argv(char **argv);
int					ft_isdigit(char c);
char				*ft_itoa(int n);
char				*ft_strjoin_sp(char *s1, char *s2);
char				*ft_strdup(const char *s1);
time_t				time_ms(void);
int					print_msg(char *dup, t_phi *phi);
int					check_death(t_phi *phi);
void				is_eating(t_phi *phi);
void				is_sleeping(t_phi *phi);
void				lock_forks(t_phi *phi);
void				unlock_forks(t_phi *phi);
t_phi				**init_phi(int options[5]);
t_phi				**free_phi(t_phi **phi, int max);
int					init_mutex(t_phi **phi, int max);

#endif
