/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 08:42:42 by user42            #+#    #+#             */
/*   Updated: 2020/12/05 11:56:23 by rturcey          ###   ########.fr       */
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
		usleep(1000);
		sem_wait(phi->eat);
		phi->time = time_ms() - phi->origin;
		if (phi->time - phi->prev_meal >= phi->time_to_die)
		{
			if (g_isdead == 0)
				print_msg(ft_strdup("died\n"), phi);
			g_isdead = 1;
			sem_post(phi->eat);
			return (NULL);
		}
		sem_post(phi->eat);
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
		is_eating(phi);
		unlock_forks(phi);
		if (check_death(phi) || (phi->nb_each && i == phi->nb_each - 1))
			break ;
		is_sleeping(phi);
		print_msg(ft_strdup("is thinking\n"), phi);
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
		pthread_create(&checks[i], NULL, check, phi[i]);
		usleep(100);
	}
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
	system("leaks philo_two");
	return (0);
}
