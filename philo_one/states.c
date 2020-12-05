/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:48:15 by rturcey           #+#    #+#             */
/*   Updated: 2020/12/05 14:52:02 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_death(t_phi *phi)
{
	phi->time = time_ms() - phi->origin;
	if (g_isdead == 0 && (phi->time - phi->prev_meal) < phi->time_to_die)
		return (0);
	return (1);
}

void	is_eating(t_phi *phi)
{
	time_t	stock;

	phi->time = time_ms() - phi->origin;
	stock = phi->time;
	phi->prev_meal = phi->time;
	print_msg(ft_strdup("is eating\n"), phi);
	pthread_mutex_lock(&phi->eat);
	while (time_ms() - phi->origin < stock + phi->time_to_eat)
	{
		usleep(100);
		if (check_death(phi))
		{
			pthread_mutex_unlock(&phi->eat);
			return ;
		}
	}
	pthread_mutex_unlock(&phi->eat);
	phi->time = time_ms() - phi->origin;
}

void	is_sleeping(t_phi *phi)
{
	time_t	stock;

	phi->time = time_ms() - phi->origin;
	stock = phi->time;
	print_msg(ft_strdup("is sleeping\n"), phi);
	while (time_ms() - phi->origin < stock + phi->time_to_sleep)
	{
		usleep(100);
		if (check_death(phi))
			return ;
	}
}

void	lock_forks(t_phi *phi)
{
	pthread_mutex_lock(&phi->forks[phi->i]);
	if (check_death(phi))
	{
		pthread_mutex_unlock(&phi->forks[phi->i]);
		return ;
	}
	print_msg(ft_strdup("has taken a fork\n"), phi);
	while (phi->nb == 1)
	{
		if (g_isdead == 0)
			usleep(100);
		else
			return ;
	}
	if (phi->i == phi->nb - 1)
		pthread_mutex_lock(&phi->forks[0]);
	else
		pthread_mutex_lock(&phi->forks[phi->i + 1]);
	if (check_death(phi))
	{
		unlock_forks(phi);
		return ;
	}
	print_msg(ft_strdup("has taken a fork\n"), phi);
}

void	unlock_forks(t_phi *phi)
{
	pthread_mutex_unlock(&phi->forks[phi->i]);
	if (phi->i == phi->nb - 1)
		pthread_mutex_unlock(&phi->forks[0]);
	else
		pthread_mutex_unlock(&phi->forks[phi->i + 1]);
}
