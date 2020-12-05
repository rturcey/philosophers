/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 09:01:30 by user42            #+#    #+#             */
/*   Updated: 2020/12/05 10:05:07 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		phi[i]->origin = 0;
		phi[i]->prev_meal = 0;
		phi[i]->nb_each = 0;
		if (options[4])
			phi[i]->nb_each = options[4];
	}
	return (phi);
}

t_phi		**parse_options(int options[5])
{
	t_phi	**phi;
	int		i;

	i = -1;
	if (options[0] < 1)
		return (print_str("You should have at least one philosopher.\n", 2));
	if (!(phi = init_phi(options)))
		return (NULL);
	if (init_sem(phi, options[0]))
	{
		print_str("Semaphore error.\n", 2);
		return (free_phi(phi, options[0]));
	}
	return (phi);
}

t_phi		**parse_argv(char **argv)
{
	int		i;
	int		j;
	int		options[5];

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (print_str("Arguments have to be integers.\n", 2));
		options[i - 1] = ft_atoi(argv[i]);
		if (options[i - 1] < 0)
			return (print_str("Your values have to be positive.\n", 2));
	}
	if (i == 5)
		options[4] = 0;
	return (parse_options(options));
}
