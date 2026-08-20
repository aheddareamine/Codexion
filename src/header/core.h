#ifndef CORE_H
# define CORE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}				t_scheduler;

typedef struct parameters
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	t_scheduler	scheduler;
}				parameters;

parameters		*parse(int argc, char **args);

#endif