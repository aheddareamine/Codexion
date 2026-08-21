/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 01:22:27 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/21 21:42:52 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CORE_H
# define CORE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct timeval	t_time;
typedef struct s_simulation	t_simulation;

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

typedef struct s_parameters
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

typedef struct s_dongle
{
	int					index;	
	int					taken;
	pthread_mutex_t		lock;
	pthread_cond_t		cond;
	long long 			available_at;
}						t_dongle;

typedef struct s_coder
{
	int					index;
	int					compile_number;
	t_coder_state		state;
	t_dongle			*left;
	t_dongle			*right;
	t_time				last_compile;
	pthread_t			thread;
	t_simulation		*sim;
}						t_coder;

typedef struct s_simulation{
	t_parameters	params;
	t_coder			*coders;
	t_dongle		*dongles;
	int				ended;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	print_lock;
	
}		t_simulation;


t_parameters			*parse(int argc, char **args);
long					gettimestamp(void);
void					set_start_time(void);
int				init_simulation(t_simulation *sim, t_parameters *params);
void			destroy_simulation(t_simulation *sim);

#endif