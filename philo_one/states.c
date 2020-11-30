/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:48:15 by rturcey           #+#    #+#             */
/*   Updated: 2020/11/30 10:54:27 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_death(t_phi *phi)
{
	phi->time = time_ms() - phi->origin;
	if ((phi->time - phi->prev_meal) < phi->time_to_die)
		return (0);
	pthread_mutex_lock(phi->print);
	if (g_isdead == 0)
		print_msg(ft_strdup("died\n"), phi);
	g_isdead = 1;
	pthread_mutex_unlock(phi->print);
	pthread_mutex_unlock(phi->take);
	return (1);
}

void	is_eating(t_phi *phi)
{
	time_t	stock;

	phi->time = time_ms() - phi->origin;
	stock = phi->time;
	phi->prev_meal = phi->time;
	print_msg(ft_strdup("is eating\n"), phi);
	while (time_ms() - phi->origin < stock + phi->time_to_eat)
	{
		if (check_death(phi))
			return ;
	}
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
		if (check_death(phi))
			return ;
	}
}

void	lock_forks(t_phi *phi)
{
	pthread_mutex_lock(phi->take);
	while (phi->try_forks[phi->i] || ((phi->i == phi->nb - 1 &&
	phi->try_forks[0]) || (phi->i < phi->nb - 1 &&
	phi->try_forks[phi->i + 1])))
	{
		if (check_death(phi))
			return ;
	}
	pthread_mutex_lock(phi->forks[phi->i]);
	if (check_death(phi))
	{
		pthread_mutex_unlock(phi->forks[phi->i]);
		return ;
	}
	phi->try_forks[phi->i] = 1;
	print_msg(ft_strdup("has taken a fork\n"), phi);
	while (phi->nb == 1)
	{
		if (check_death(phi))
			return ;
	}
	if (phi->i == phi->nb - 1 && pthread_mutex_lock(phi->forks[0]) == 0)
		phi->try_forks[0] = 1;
	else if (pthread_mutex_lock(phi->forks[phi->i + 1]) == 0)
		phi->try_forks[phi->i + 1] = 1;
	if (check_death(phi))
		return ;
	print_msg(ft_strdup("has taken a fork\n"), phi);
	pthread_mutex_unlock(phi->take);
}

void	unlock_forks(t_phi *phi)
{
	pthread_mutex_unlock(phi->forks[phi->i]);
	phi->try_forks[phi->i] = 0;
	if (phi->i == phi->nb - 1)
	{
		pthread_mutex_unlock(phi->forks[0]);
		phi->try_forks[0] = 0;
	}
	else
	{
		pthread_mutex_unlock(phi->forks[phi->i + 1]);
		phi->try_forks[phi->i + 1] = 0;
	}
}
