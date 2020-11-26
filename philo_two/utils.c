/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:45:42 by user42            #+#    #+#             */
/*   Updated: 2020/11/26 12:00:00 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			init_sem(t_phi **phi, int max)
{
	int		i;
	sem_t	*forks;
	sem_t	*print;

	i = -1;
	if (!(forks = sem_open("forks", O_CREAT)))
		return (-1);
	if (!(print = sem_open("print", O_CREAT)))
		return (-1);
	sem_post(print);
	while (++i < max)
	{
		phi[i]->print = print;
		phi[i]->forks = forks;
		sem_post(forks);
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
		g_forks = options[0];
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
	if (phi && phi[0])
	{
		sem_close(phi[0]->forks);
		sem_unlink("forks");
	}
	if (phi && phi[0])
	{
		sem_close(phi[0]->print);
		sem_unlink("print");
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
