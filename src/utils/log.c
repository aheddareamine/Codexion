/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:00:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/22 17:43:43 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

static const char	*state_to_msg(t_coder_state state)
{
	if (state == COMPILING)
		return ("is compiling");
	if (state == DEBUGGING)
		return ("is debugging");
	return ("is refactoring");
}

void	print_log(t_coder *coder, const char *msg)
{
	pthread_mutex_lock(&coder->sim->print_lock);
	printf("%ld %d %s\n", gettimestamp(), coder->index, msg);
	pthread_mutex_unlock(&coder->sim->print_lock);
}

void	log_state(t_coder *coder)
{
	print_log(coder, state_to_msg(coder->state));
}

void	log_dongle(t_coder *coder)
{
	print_log(coder, "has taken a dongle");
}
