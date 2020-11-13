/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:48:15 by rturcey           #+#    #+#             */
/*   Updated: 2020/11/13 11:37:56 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_death(t_phi *phi)
{
	phi->time = time_ms() - phi->origin;
	if ((phi->time - phi->prev_meal) < phi->time_to_die)
		return (0);
	print_msg(ft_strdup("died\n"), phi);
	phi->isdead = 1;
	return (1);
}

void	is_eating(t_phi *phi)
{
	phi->time = time_ms() - phi->origin;
	phi->prev_meal = phi->time;
	print_msg(ft_strdup("is eating\n"), phi);
	usleep(phi->time_to_eat / 1000);
	phi->time = time_ms() - phi->origin;
	phi->prev_meal = phi->time;
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
		pthread_mutex_lock((*(phi->forks)[0]));
	else
		pthread_mutex_lock((*(phi->forks)[phi->i + 1]));
	if (check_death(phi))
		return ;
	print_msg(ft_strdup("has taken a fork\n"), phi);
	pthread_mutex_lock((*(phi->forks)[phi->i]));
	if (check_death(phi))
		return ;
	print_msg(ft_strdup("has taken a fork\n"), phi);
}

void	unlock_forks(t_phi *phi)
{
	if (phi->i == phi->nb - 1)
		pthread_mutex_unlock((*(phi->forks)[0]));
	else
		pthread_mutex_unlock((*(phi->forks)[phi->i + 1]));
	pthread_mutex_unlock((*(phi->forks)[phi->i]));
}
