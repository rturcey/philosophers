/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:27:09 by rturcey           #+#    #+#             */
/*   Updated: 2020/12/05 11:06:59 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	char	*haycast;

	if (!haystack)
		return (NULL);
	haycast = (char *)haystack;
	i = 0;
	if (!needle[0])
		return (haycast);
	while (haycast[i])
	{
		j = 0;
		while (haycast[i + j] && needle[j]
			&& haycast[i + j] == needle[j])
			j++;
		if (!(needle[j]))
			return (&haycast[i]);
		i++;
	}
	return (NULL);
}

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
		{
			pthread_create(&phi[i]->thread, NULL, check, phi[i]);
			philosophize(phi[i]);
		}
	}
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
		phi[i]->eat = NULL;
		phi[i]->death = NULL;
		phi[i]->origin = 0;
		phi[i]->prev_meal = 0;
		phi[i]->nb_each = 0;
		if (options[4])
			phi[i]->nb_each = options[4];
	}
	return (phi);
}
