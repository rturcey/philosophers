/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 09:01:30 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 10:32:30 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_phi		**parse_options(int options[5])
{
	t_phi	**phi;
	int		i;

	i = -1;
	if (options[0] < 1)
		return (print_str("You should have at least one philosopher.\n", 2));
	if (!(phi = init_phi(options)))
		return (NULL);
	if (init_mutex(phi, options[0]))
		return (free_phi(phi, options[0]));
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
