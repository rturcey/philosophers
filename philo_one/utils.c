/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:45:42 by user42            #+#    #+#             */
/*   Updated: 2020/11/16 12:40:35 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			*init_try(int max)
{
	int		i;
	int		*try_forks;

	i = -1;
	if (!(try_forks = malloc(sizeof(int) * max)))
		return (NULL);
	while (++i < max)
		try_forks[i] = 0;
	return (try_forks);
}

int			init_mutex(t_phi **phi, int max)
{
	int				i;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*print;
	int				*try_forks;

	i = -1;
	if (!(forks = malloc(sizeof(pthread_mutex_t *) * (max))))
		return (-1);
	if (!(try_forks = init_try(max)))
		return (-1);
	while (++i < max)
	{
		if (!(forks[i] = malloc(sizeof(pthread_mutex_t))))
			return (-1);
		pthread_mutex_init(forks[i], NULL);
	}
	if (!(print = malloc(sizeof(pthread_mutex_t))))
		return (-1);
	pthread_mutex_init(print, NULL);
	while (--i >= 0 && (phi[i]->forks = forks))
	{
		phi[i]->print = print;
		phi[i]->try_forks = try_forks;
	}
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
		phi[i]->print = NULL;
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
			free(phi[0]->forks[i]);
		free(phi[0]->forks);
	}
	free(phi[0]->try_forks);
	if (phi && phi[0] && phi[0]->print)
		free(phi[0]->print);
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
