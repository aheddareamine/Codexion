#include "./header/core.h"

void print_parameters(t_parameters params)
{
    printf("number_of_coders           : %d\n", params.number_of_coders);
    printf("time_to_burnout            : %d\n", params.time_to_burnout);
    printf("time_to_compile            : %d\n", params.time_to_compile);
    printf("time_to_debug              : %d\n", params.time_to_debug);
    printf("time_to_refactor           : %d\n", params.time_to_refactor);
    printf("number_of_compiles_required: %d\n", params.number_of_compiles_required);
    printf("dongle_cooldown            : %d\n", params.dongle_cooldown);
}

int	main(int argc, char **argv)
{
	set_start_time();
	// t_parameters *parameters = parse(argc, argv);
	// if (!parameters)
	// 	return (1);
	// print_parameters(*parameters);
	t_time test;
	sleep(5);
	long	time = gettimestamp();
	printf("%ld\n", time);
	return (0);
}
