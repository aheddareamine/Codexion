/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 21:34:58 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/21 21:57:22 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/core.h"

static int	init_dongles(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		sim->dongles[i].index = i;
		sim->dongles[i].taken = 0;
		sim->dongles[i].available_at = 0;
		if (pthread_mutex_init(&sim->dongles[i].lock, NULL) != 0)
			return (0);
		if (pthread_cond_init(&sim->dongles[i].cond, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static void	init_coders(t_simulation *sim)
{
	int	i;
	int	n;

	n = sim->params.number_of_coders;
	i = 0;
	while (i < n)
	{
		sim->coders[i].index = i + 1;
		sim->coders[i].compile_number = 0;
		sim->coders[i].state = REFACTORING;
		sim->coders[i].left = &sim->dongles[i];
		sim->coders[i].right = &sim->dongles[(i + 1) % n];
		sim->coders[i].sim = sim;
		i++;
	}
}

int	init_simulation(t_simulation *sim, t_parameters *params)
{
	sim->params = *params;
	sim->coders = malloc(sizeof(t_coder) * params->number_of_coders);
	sim->dongles = malloc(sizeof(t_dongle) * params->number_of_coders);
	if (!sim->coders || !sim->dongles)
		return (0);
	sim->ended = 0;
	if (pthread_mutex_init(&sim->end_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		return (0);
	if (!init_dongles(sim))
		return (0);
	init_coders(sim);
	return (1);
}

void	destroy_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->params.number_of_coders)
	{
		pthread_mutex_destroy(&sim->dongles[i].lock);
		pthread_cond_destroy(&sim->dongles[i].cond);
		i++;
	}
	pthread_mutex_destroy(&sim->end_lock);
	pthread_mutex_destroy(&sim->print_lock);
	free(sim->coders);
	free(sim->dongles);
}