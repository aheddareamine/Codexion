/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 01:22:27 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/21 10:05:11 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct timeval	t_time;

typedef enum e_scheduler
{
	FIFO,
	EDF
}						t_scheduler;

typedef enum e_coder_state
{
	COMPILING,
	DEBUGGING,
	REFACTORING
}						t_coder_state;

typedef struct parameters
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	t_scheduler			scheduler;
}						t_parameters;

typedef struct coder
{
	int					index;
	int					compilation_number;
	t_coder_state		state;
	pthread_t			*thread;
}						t_coder;

typedef struct dongle
{
	int					index;
	int					cooldow;
	int					taken;
}						t_dongle;

typedef struct simulation
{
	int					nb_coders;
	t_coder				*coders;
	t_dongle			*dongles;
}						t_simulation;

t_parameters			*parse(int argc, char **args);
long					gettimestamp(void);
void					set_start_time(void);

#endif