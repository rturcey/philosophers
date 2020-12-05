/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:42:51 by user42            #+#    #+#             */
/*   Updated: 2020/12/05 12:10:41 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/time.h>
# include <semaphore.h>

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
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eat;
	sem_t			*death;
	char			*name;
	pthread_t		thread;

}					t_phi;

int		g_isdead;
int		g_end;

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
int					init_sem(t_phi **phi, int max);
void				*check(void *arg);

#endif
