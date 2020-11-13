/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 09:01:30 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 10:55:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		clear_mutex(t_phi *phi)
{
	int		i;

	i = -1;
	while (++i < phi->nb)
	{
		pthread_mutex_destroy(phi->forks[i]);
		free(phi->forks[i]);
	}
	free(phi->forks);
	return (-1);
}

static int	init_forks(t_phi *phi)
{
	int		i;

	i = -1;
	if (!(phi->forks = malloc(sizeof(pthread_mutex_t) * (phi->nb))))
		return (-1);
	while (++i < phi->nb)
	{
		if (!(phi->forks[i] = malloc(sizeof(pthread_mutex_t))))
			return (-1);
		pthread_mutex_init(phi->forks[i], NULL);
	}
	if (!(phi->prev_meal = malloc(sizeof(time_t) * phi->nb)))
		return (clear_mutex(phi));
	return (0);
}

t_phi		*parse_options(int options[5])
{
	t_phi	*phi;

	if (options[0] < 1)
		return (print_str("You should have at least one philosopher.\n", 2));
	if (!(phi = malloc(sizeof(t_phi))))
		return (NULL);
	phi->nb = options[0];
	phi->time_to_die = options[1];
	phi->time_to_eat = options[2];
	phi->time_to_sleep = options[3];
	phi->isdead = 0;
	if (options[4])
		phi->nb_each = options[4];
	else
		phi->nb_each = 0;
	if (init_forks(phi))
	{
		free(phi);
		return (NULL);
	}
	return (phi);
		
}

t_phi		*parse_argv(char **argv)
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