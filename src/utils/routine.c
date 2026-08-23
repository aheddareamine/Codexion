/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:00:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/23 20:19:02 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

static void	order_dongles(t_coder *coder, t_dongle **low, t_dongle **high)
{
	if (coder->left->index <= coder->right->index)
	{
		*low = coder->left;
		*high = coder->right;
	}
	else
	{
		*low = coder->right;
		*high = coder->left;
	}
}

void	take_dongles(t_coder *coder)
{
	t_dongle	*low;
	t_dongle	*high;

	order_dongles(coder, &low, &high);
	acquire_dongle(coder, low);
	acquire_dongle(coder, high);
}

void	release_dongles(t_coder *coder)
{
	t_dongle	*low;
	t_dongle	*high;

	order_dongles(coder, &low, &high);
	release_dongle(coder, high);
	release_dongle(coder, low);
}

static void	run_cycle(t_coder *coder)
{
	t_parameters	*p;

	p = &coder->sim->params;
	take_dongles(coder);
	coder->state = COMPILING;
	gettimeofday(&coder->last_compile, NULL);
	log_state(coder);
	usleep(p->time_to_compile * 1000);
	coder->compile_number++;
	release_dongles(coder);
	coder->state = DEBUGGING;
	log_state(coder);
	usleep(p->time_to_debug * 1000);
	coder->state = REFACTORING;
	log_state(coder);
	usleep(p->time_to_refactor * 1000);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	int		required;

	coder = (t_coder *)arg;
	required = coder->sim->params.number_of_compiles_required;
	while (!is_ended(coder->sim) && coder->compile_number < required)
		run_cycle(coder);
	return (NULL);
}
