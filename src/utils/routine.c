/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:00:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/22 17:43:20 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

static void	acquire_one(t_dongle *dongle)
{
	(void)dongle;
}

void	take_dongles(t_coder *coder)
{
	acquire_one(coder->left);
	log_dongle(coder);
	acquire_one(coder->right);
	log_dongle(coder);
}

/*
** release_dongles: STUB for Day 3. Will mark both dongles free, stamp
** available_at = now + dongle_cooldown, and signal waiters on each cond.
*/
void	release_dongles(t_coder *coder)
{
	(void)coder;
}

/*
** run_cycle: one full turn of the coder's life. Take both dongles, compile
** (holding them), release, debug, refactor. State is set BEFORE each log_state
** so the enum-driven logger prints the right line. last_compile is stamped at
** the START of compiling because the burnout deadline is measured from there
** (Day 4). compile_number is incremented once a compile completes.
*/
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

/*
** coder_routine: the function each coder thread runs.
** The while condition has a Day-2 PLACEHOLDER: a coder stops once it has
** personally compiled number_of_compiles_required times, purely so the test
** terminates. The REAL rule (Day 4) is global -- the simulation stops when
** EVERY coder has reached the threshold, or when one burns out -- and will be
** enforced by the monitor setting the shared `ended` flag, which is why the
** is_ended() check is already here on the left of the &&.
*/
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
