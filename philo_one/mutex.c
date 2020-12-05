/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:01:58 by rturcey           #+#    #+#             */
/*   Updated: 2020/12/05 11:26:14 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t	*create_mutex(void)
{
	pthread_mutex_t	*new;

	pthread_mutex_init(new, NULL);
	return (new);
}

int				init_mutex(t_phi **phi, int max)
{
	int				i;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*take;

	i = -1;
	if (!(forks = malloc(sizeof(pthread_mutex_t *) * (max))))
		return (-1);
	while (++i < max)
		if (!(forks[i] = create_mutex()))
			return (-1);
	if (!(print = create_mutex()))
		return (-1);
	if (!(take = create_mutex()))
		return (-1);
	while (--i >= 0)
	{
		phi[i]->forks = forks;
		phi[i]->print = print;
		if (!(phi[i]->eat = create_mutex()))
			return (-1);
	}
	return (0);
}
