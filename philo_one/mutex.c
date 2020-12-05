/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:01:58 by rturcey           #+#    #+#             */
/*   Updated: 2020/12/05 14:27:46 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				init_mutex(t_phi **phi, int max)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	if (!(forks = malloc(sizeof(pthread_mutex_t) * (max))))
		return (-1);
	while (++i < max)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&phi[0]->print, NULL);
	while (--i >= 0)
	{
		phi[i]->forks = forks;
		phi[i]->print = phi[0]->print;
		pthread_mutex_init(&phi[i]->eat, NULL);
	}
	return (0);
}
