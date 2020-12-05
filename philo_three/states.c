/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:48:15 by rturcey           #+#    #+#             */
/*   Updated: 2020/12/05 10:54:35 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_death(t_phi *phi)
{
	phi->time = time_ms() - phi->origin;
	if (g_isdead == 0 && ((phi->time - phi->prev_meal) < phi->time_to_die))
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
	sem_wait(phi->eat);
	while (time_ms() - phi->origin < stock + phi->time_to_eat)
	{
		usleep(100);
		if (check_death(phi))
		{
			sem_post(phi->eat);
			return ;
		}
	}
	sem_post(phi->eat);
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
	sem_wait(phi->forks);
	print_msg(ft_strdup("has taken a fork\n"), phi);
	while (phi->nb == 1)
	{
		if (check_death(phi))
			return ;
	}
	sem_wait(phi->forks);
	print_msg(ft_strdup("has taken a fork\n"), phi);
}

void	unlock_forks(t_phi *phi)
{
	sem_post(phi->forks);
	sem_post(phi->forks);
}
