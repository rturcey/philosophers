/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:45:42 by user42            #+#    #+#             */
/*   Updated: 2020/12/01 12:43:13 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			print_msg(char *dup, t_phi *phi)
{
	char	*msg;

	sem_wait(phi->print);
	if (g_isdead == 1)
	{
		free(dup);
		sem_post(phi->print);
		return (0);
	}
	if (!(msg = ft_itoa(phi->time)))
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
	if (g_isdead < 1)
		print_str(msg, 1);
	free(msg);
	if (g_isdead == -1)
		g_isdead = 1;
	sem_post(phi->print);
	return (0);
}

int			init_sem(t_phi **phi, int max)
{
	int		i;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*take;

	forks = sem_open("forks", O_CREAT, 0644, max);
	print = sem_open("print", O_CREAT, 0644, 1);
	take = sem_open("take", O_CREAT, 0644, 1);
	i = -1;
	while (++i < max)
	{
		phi[i]->print = print;
		phi[i]->forks = forks;
		phi[i]->take = take;
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
		phi[i]->take = NULL;
		phi[i]->origin = 0;
		phi[i]->prev_meal = 0;
		phi[i]->nb_each = 0;
		if (options[4])
			phi[i]->nb_each = options[4];
	}
	return (phi);
}

t_phi		**free_phi(t_phi **phi, int max)
{
	int		i;

	i = -1;
	sem_close(phi[0]->forks);
	sem_unlink("forks");
	sem_close(phi[0]->print);
	sem_unlink("print");
	sem_close(phi[0]->take);
	sem_unlink("take");
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
