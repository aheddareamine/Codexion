#include "./header/core.h"

static int	check_on_numbers(char **argv)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	while (i <= 7)
	{
		j = 0;
		if (!argv[i][j])
			return (0);
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static t_parameters	*init_parameters(char **argv)
{
	t_parameters	*params;

	params = malloc(sizeof(t_parameters));
	if (!params)
		return (NULL);
	params->number_of_coders = atoi(argv[1]);
	params->time_to_burnout = atoi(argv[2]);
	params->time_to_compile = atoi(argv[3]);
	params->time_to_debug = atoi(argv[4]);
	params->time_to_refactor = atoi(argv[5]);
	params->number_of_compiles_required = atoi(argv[6]);
	params->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "fifo") == 0)
		params->scheduler = FIFO;
	else if (strcmp(argv[8], "edf") == 0)
		params->scheduler = EDF;
	return (params);
}

t_parameters	*parse(int argc, char **argv)
{
	if (argc != 9 || (strcmp(argv[8], "fifo") && strcmp(argv[8], "edf"))
		|| !check_on_numbers(argv))
	{
		fprintf(stderr, "parameters should follow the format:\n\
[number_of_coders] [time_to_burnout] [time_to_compile] [time_to_debug] \
[time_to_refactor] [number_of_compiles_required] [dongle_cooldown] [scheduler] \
\n");
		return (NULL);
	}
	return (init_parameters(argv));
}
