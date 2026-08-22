/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 01:22:31 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/22 17:41:20 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/core.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_parameters	*parameters;

	parameters = parse(argc, argv);
	if (!parameters)
		return (1);
	if (!init_simulation(&sim, parameters))
	{
		free(parameters);
		return (1);
	}
	free(parameters);
	set_start_time();
	run_simulation(&sim);
	destroy_simulation(&sim);
	return (0);
}
