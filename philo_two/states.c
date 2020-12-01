/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:48:15 by rturcey           #+#    #+#             */
/*   Updated: 2020/12/01 12:58:24 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		check_death(t_phi *phi)
{
	phi->time = time_ms() - phi->origin;
	if ((phi->time - phi->prev_meal) < phi->time_to_die)
		return (0);
	sem_wait(phi->print);
	if (g_isdead == 0)
		print_msg(ft_strdup("died\n"), phi);
	g_isdead = 1;
	sem_post(phi->print);
	return (1);
}

void	is_eating(t_phi *phi)
{
	time_t	stock;

	phi->time = time_ms() - phi->origin;
	stock = phi->time;
	if (check_death(phi))
		return ;
	phi->prev_meal = phi->time;
	print_msg(ft_strdup("is eating\n"), phi);
	while (time_ms() - phi->origin < stock + phi->time_to_eat)
		if (check_death(phi))
			return ;
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
	if (check_death(phi))
		return ;
	sem_wait(phi->take);
	if (check_death(phi))
		return ;
	sem_wait(phi->forks);
	if (check_death(phi))
		return ;
	print_msg(ft_strdup("has taken a fork\n"), phi);
	sem_wait(phi->forks);
	if (check_death(phi))
		return ;
	print_msg(ft_strdup("has taken a fork\n"), phi);
	sem_post(phi->take);
}

void	unlock_forks(t_phi *phi)
{
	sem_post(phi->forks);
	sem_post(phi->forks);
}
