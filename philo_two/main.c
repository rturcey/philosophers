/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:42:42 by user42            #+#    #+#             */
/*   Updated: 2020/12/01 12:43:15 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

time_t	time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*check(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (g_isdead == 0 && g_end < phi->nb)
	{
		if (time_ms() - phi->origin - phi->prev_meal >= phi->time_to_die)
		{
			phi->time = time_ms() - phi->origin;
			if (g_isdead == 0 && (g_isdead = -1))
				print_msg(ft_strdup("died\n"), phi);
			sem_post(phi->take);
			return (NULL);
		}
	}
	return (NULL);
}

void	*philosophize(void *arg)
{
	t_phi	*phi;
	int		i;

	phi = (t_phi *)arg;
	phi->time = 0;
	phi->prev_meal = 0;
	i = -1;
	while (g_isdead == 0 && (!phi->nb_each || ++i < phi->nb_each))
	{
		lock_forks(phi);
		if (g_isdead == 1 || check_death(phi))
			return (NULL);
		is_eating(phi);
		if (g_isdead == 1 || check_death(phi))
			return (NULL);
		unlock_forks(phi);
		if (g_isdead || (phi->nb_each && i == phi->nb_each - 1))
			break ;
		is_sleeping(phi);
		if (g_isdead == 1 || check_death(phi))
			return (NULL);
		print_msg(ft_strdup("is thinking\n"), phi);
		sem_post(phi->print);
	}
	g_end++;
	return (NULL);
}

void	launch_threads(t_phi **phi)
{
	pthread_t	*checks;
	int			i;

	if (!(checks = malloc(sizeof(pthread_t) * phi[0]->nb)))
		return ;
	i = -1;
	phi[0]->origin = time_ms();
	while (++i < phi[0]->nb)
	{
		phi[i]->origin = phi[0]->origin;
		pthread_create(&phi[i]->thread, NULL, philosophize, phi[i]);
	}
	i = -1;
	while (++i < phi[0]->nb)
		pthread_create(&checks[i], NULL, check, phi[i]);
	i = -1;
	while (++i < phi[0]->nb)
	{
		pthread_detach(phi[i]->thread);
		pthread_join(checks[i], NULL);
	}
	free(checks);
}

int		main(int argc, char **argv)
{
	t_phi	**phi;
	int		i;

	i = -1;
	g_isdead = 0;
	g_end = 0;
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("take");
	if (argc < 5 || argc > 6)
	{
		print_str("Incorrect number of arguments.\n", 2);
		return (-1);
	}
	if (!(phi = parse_argv(argv)))
		return (-1);
	launch_threads(phi);
	free_phi(phi, phi[0]->nb);
	return (0);
}
