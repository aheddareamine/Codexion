#ifndef CORE_H
# define CORE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <sys/time.h>

typedef struct timeval t_time;

typedef enum e_scheduler
{
	FIFO,
	EDF
}					t_scheduler;

typedef enum e_coder_state
{
	COMPILING,
	DEBUGGING,
	REFACTORING
}					t_coder_state;

typedef struct parameters
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_scheduler		scheduler;
}					t_parameters;

typedef struct coder
{
	int				index;
	int				compilation_number;
	t_coder_state	state;
	pthread_t		*thread;
}					t_coder;

typedef struct dongle
{
	int				taken;
	int				index;
}					t_dongle;

t_parameters		*parse(int argc, char **args);
long				gettimestamp(void);
void				set_start_time(void);

#endif