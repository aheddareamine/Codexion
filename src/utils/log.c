/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:00:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/23 20:21:23 by aaheddar         ###   ########.fr       */
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
	char	buf[128];
	int		len;

	len = 0;
	pthread_mutex_lock(&coder->sim->print_lock);
	len += put_ulong(buf + len, gettimestamp());
	buf[len++] = ' ';
	len += put_ulong(buf + len, coder->index);
	buf[len++] = ' ';
	len += put_str(buf + len, msg);
	buf[len++] = '\n';
	write(1, buf, len);
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
