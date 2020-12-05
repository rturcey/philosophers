/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:45:42 by user42            #+#    #+#             */
/*   Updated: 2020/12/05 14:39:49 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			print_msg(char *dup, t_phi *phi)
{
	char	*msg;

	if (!(msg = ft_itoa(time_ms() - phi->origin)))
	{
		free(dup);
		return (-1);
	}
	if (!(msg = ft_strjoin_sp(msg, ft_itoa(phi->i + 1))))
	{
		free(dup);
		return (-1);
	}
	if (!(msg = ft_strjoin_sp(msg, dup)))
		return (-1);
	pthread_mutex_lock(&phi->print);
	if (g_isdead == 0)
		print_str(msg, 1);
	free(msg);
	pthread_mutex_unlock(&phi->print);
	return (0);
}

t_phi		**init_phi(int options[5])
{
	int		i;
	t_phi	**phi;

	i = -1;
	if (!(phi = malloc(options[0] * sizeof(t_phi))))
		return (NULL);
	while (++i < options[0])
	{
		if (!(phi[i] = malloc(sizeof(t_phi))))
			return (free_phi(phi, options[0]));
		phi[i]->nb = options[0];
		phi[i]->time_to_die = options[1];
		phi[i]->time_to_eat = options[2];
		phi[i]->time_to_sleep = options[3];
		phi[i]->i = i;
		phi[i]->forks = NULL;
		if (options[4])
			phi[i]->nb_each = options[4];
		else
			phi[i]->nb_each = 0;
	}
	return (phi);
}

t_phi		**free_phi(t_phi **phi, int max)
{
	int		i;

	i = -1;
	if (phi && phi[0] && phi[0]->forks)
	{
		while (++i < max)
			pthread_mutex_destroy(&phi[0]->forks[i]);
		free(phi[0]->forks);
	}
	if (phi && phi[0])
	{
		pthread_mutex_destroy(&phi[0]->print);
		pthread_mutex_destroy(&phi[0]->eat);
	}
	i = -1;
	while (++i < max)
		free(phi[i]);
	free(phi);
	return (NULL);
}

void		*print_str(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
	return (NULL);
}
