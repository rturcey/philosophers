/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:45:42 by user42            #+#    #+#             */
/*   Updated: 2020/12/05 11:17:19 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	sem_wait(phi->print);
	if (g_isdead == 0)
		print_str(msg, 1);
	free(msg);
	sem_post(phi->print);
	return (0);
}

sem_t		*init_eat(t_phi *phi)
{
	if (!(phi->name = ft_strjoin_sp(ft_strdup("eat"), ft_itoa(phi->i))))
		return (NULL);
	sem_unlink(phi->name);
	return (sem_open(phi->name, O_CREAT, 0644, 1));
}

int			init_sem(t_phi **phi, int max)
{
	int		i;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*death;

	forks = sem_open("forks", O_CREAT, 0644, max);
	print = sem_open("print", O_CREAT, 0644, 1);
	death = sem_open("death", O_CREAT, 0644, 1);
	i = -1;
	while (++i < max)
	{
		phi[i]->print = print;
		phi[i]->forks = forks;
		phi[i]->death = death;
		if (!(phi[i]->eat = init_eat(phi[i])))
			return (-1);
	}
	return (0);
}

t_phi		**free_phi(t_phi **phi, int max)
{
	int		i;

	i = -1;
	sem_close(phi[0]->forks);
	sem_unlink("forks");
	sem_close(phi[0]->print);
	sem_unlink("print");
	sem_close(phi[0]->death);
	sem_unlink("death");
	i = -1;
	while (++i < max)
	{
		sem_close(phi[i]->eat);
		sem_unlink(phi[i]->name);
		free(phi[i]->name);
		free(phi[i]);
	}
	free(phi);
	return (NULL);
}

void		*print_str(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
	return (NULL);
}
