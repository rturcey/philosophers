/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:42:42 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 11:39:07 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

#include <string.h>

time_t	time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int		print_msg(char *dup, t_phi *phi)
{
	char	*msg;

	pthread_mutex_lock(*phi->print);
	if (!(msg = ft_itoa(phi->time)))
		return (-1);
	if (!(msg = ft_strjoin_sp(msg, ft_itoa(phi->i + 1))))
		return (-1);
	if (!(msg = ft_strjoin_sp(msg, dup)))
		return (-1);
	print_str(msg, 1);
	free(msg);
	pthread_mutex_unlock(*phi->print);
	return (0);
}

void	*philosophize(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	phi->origin = time_ms();
	phi->time = 0;
	while(phi->isdead == 0)
	{
		lock_forks(phi);
		if (phi->isdead == 1 || check_death(phi))
			return (NULL);
		is_eating(phi);
		unlock_forks(phi);
		is_sleeping(phi);
		if (phi->isdead == 1 || check_death(phi))
			return (NULL);
		print_msg(ft_strdup("is thinking\n"), phi);
	}
	return (NULL);
}

void	launch_threads(t_phi **phi)
{
	pthread_t	*threads;
	int			i;

	if (!(threads = malloc(sizeof(pthread_t) * phi[0]->nb)))
		return ;
	i = -1;
	while (++i < phi[0]->nb)
		pthread_create(&threads[i], NULL, philosophize, phi[i]);
	i = -1;
	while (++i < phi[0]->nb)
		pthread_join(threads[i], NULL);
	free (threads);
}

int		main(int argc, char **argv)
{
	t_phi	**phi;
	int		i;

	i = -1;
	if (argc < 5 || argc > 6)
	{
		print_str("Incorrect number of arguments.\n", 2);
		return (-1);
	}
	if (!(phi = parse_argv(argv)))
		return (-1);
	launch_threads(phi);
	free_phi(phi, phi[0]->nb);
	return (0);
}
