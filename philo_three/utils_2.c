/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:27:09 by rturcey           #+#    #+#             */
/*   Updated: 2020/11/30 10:34:53 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	process(t_phi **phi)
{
	int		i;

	i = 0;
	phi[0]->origin = time_ms();
	while (++i < phi[0]->nb)
		phi[i]->origin = phi[0]->origin;
	i = -1;
	while (++i < phi[0]->nb)
	{
		if ((phi[i]->pid = fork()) < 0)
		{
			print_str("Fork error.\n", 2);
			exit(1);
		}
		else if (phi[i]->pid == 0)
			philosophize(phi[i]);
	}
}
