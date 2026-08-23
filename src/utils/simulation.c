/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:00:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/23 20:20:30 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (!is_ended(sim))
		usleep(1000);
	return (NULL);
}

static int	create_threads(t_simulation *sim, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, &sim->coders[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, sim) != 0)
		return (0);
	return (1);
}

static void	join_threads(t_simulation *sim, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
	set_ended(sim);
	pthread_join(monitor, NULL);
}

int	run_simulation(t_simulation *sim)
{
	pthread_t	monitor;

	if (!create_threads(sim, &monitor))
		return (0);
	join_threads(sim, monitor);
	return (1);
}
