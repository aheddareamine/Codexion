/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 01:22:31 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/21 01:24:04 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/core.h"

void	print_parameters(t_parameters params)
{
	printf("number_of_coders           : %d\n", params.number_of_coders);
	printf("time_to_burnout            : %d\n", params.time_to_burnout);
	printf("time_to_compile            : %d\n", params.time_to_compile);
	printf("time_to_debug              : %d\n", params.time_to_debug);
	printf("time_to_refactor           : %d\n", params.time_to_refactor);
	printf("number_of_compiles_required: %d\n",
		params.number_of_compiles_required);
	printf("dongle_cooldown            : %d\n", params.dongle_cooldown);
}

int	main(int argc, char **argv)
{
	t_time			test;
	long			time;
	t_parameters	*parameters;

	set_start_time();
	parameters = parse(argc, argv);
	if (!parameters)
		return (1);
	print_parameters(*parameters);
	sleep(5);
	time = gettimestamp();
	printf("%ld\n", time);
	return (0);
}
