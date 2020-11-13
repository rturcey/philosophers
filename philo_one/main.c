/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:42:42 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 11:17:34 by user42           ###   ########.fr       */
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

	if (!(msg = ft_itoa(phi->time)))
		return (-1);
	if (!(msg = ft_strjoin_sp(msg, ft_itoa(phi->i + 1))))
		return (-1);
	if (!(msg = ft_strjoin_sp(msg, dup)))
		return (-1);
	print_str(msg, 1);
	free(msg);
	return (0);
}

#include <stdio.h>

int		check_death(t_phi *phi)
{
	phi->time = time_ms() - phi->origin;
	if ((phi->time - phi->prev_meal[phi->i]) < phi->time_to_die)
		return (0);
	print_msg(ft_strdup("died\n"), phi);
	phi->isdead = 1;
	return (1);
}

void	is_eating(t_phi *phi)
{
	phi->time = time_ms() - phi->origin;
	phi->prev_meal[phi->i] = phi->time;
	print_msg(ft_strdup("is eating\n"), phi);
	usleep(phi->time_to_eat / 1000);
	phi->time = time_ms() - phi->origin;
	phi->prev_meal[phi->i] = phi->time;
}

void	is_sleeping(t_phi *phi)
{
	time_t	stock;

	phi->time = time_ms() - phi->origin;
	stock = phi->time;
	print_msg(ft_strdup("is sleeping\n"), phi);
	while (phi->time < stock + phi->time_to_sleep)
	{
		if (check_death(phi))
			return ;
		phi->time = time_ms();
	}
}

void	lock_forks(t_phi *phi)
{
	if (phi->i == phi->nb - 1)
		pthread_mutex_lock(phi->forks[0]);
	else
		pthread_mutex_lock(phi->forks[phi->i + 1]);
	if (check_death(phi))
		return ;
	print_msg(ft_strdup("has taken a fork\n"), phi);
	pthread_mutex_lock(phi->forks[phi->i]);
	if (check_death(phi))
		return ;
	print_msg(ft_strdup("has taken a fork\n"), phi);
}

void	unlock_forks(t_phi *phi)
{
	if (phi->i == phi->nb - 1)
		pthread_mutex_unlock(phi->forks[0]);
	else
		pthread_mutex_unlock(phi->forks[phi->i + 1]);
	pthread_mutex_unlock(phi->forks[phi->i]);
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

void	launch_threads(t_phi *phi)
{
	pthread_t	*threads;

	if (!(threads = malloc(sizeof(pthread_t) * phi->nb)))
		return ;
	phi->i = -1;
	while (++phi->i < phi->nb && phi->isdead == 0)
		pthread_create(&threads[phi->i], NULL, philosophize, phi);
	phi->i = -1;
	while (++phi->i < phi->nb)
		pthread_join(threads[phi->i], NULL);
	free (threads);
}

int		main(int argc, char **argv)
{
	t_phi	*phi;
	int		i;
	
	i = -1;
	if (argc < 5 || argc > 6)
	{
		print_str("Incorrect number of arguments.\n", 2);
		return (-1);
	}
	if (!(phi = parse_argv(argv)))
		return (-1);
	if (!(*(phi->print) = malloc(sizeof(pthread_mutex_t))))
		return (-1);
	pthread_mutex_init(*(phi->print), NULL);
	launch_threads(phi);
	clean_phi(phi);
	return (0);
}