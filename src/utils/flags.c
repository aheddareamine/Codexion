/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:00:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/23 20:21:34 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

int	is_ended(t_simulation *sim)
{
	int	ended;

	pthread_mutex_lock(&sim->end_lock);
	ended = sim->ended;
	pthread_mutex_unlock(&sim->end_lock);
	return (ended);
}

void	set_ended(t_simulation *sim)
{
	pthread_mutex_lock(&sim->end_lock);
	sim->ended = 1;
	pthread_mutex_unlock(&sim->end_lock);
}
