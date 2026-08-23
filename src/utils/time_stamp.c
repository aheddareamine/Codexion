/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 01:22:35 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/23 20:20:05 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

static t_time	*get_start_time(void)
{
	static t_time	start_time;

	return (&start_time);
}

void	set_start_time(void)
{
	gettimeofday(get_start_time(), NULL);
}

long	gettimestamp(void)
{
	t_time	*start_time;
	t_time	present_time;

	start_time = get_start_time();
	gettimeofday(&present_time, NULL);
	return ((present_time.tv_sec - start_time->tv_sec) * 1000
		+ (present_time.tv_usec - start_time->tv_usec) / 1000);
}

long	ms_since_start(t_time *event)
{
	t_time	*start_time;

	start_time = get_start_time();
	return ((event->tv_sec - start_time->tv_sec) * 1000
		+ (event->tv_usec - start_time->tv_usec) / 1000);
}

void	future_abstime(long ms_from_now, struct timespec *ts)
{
	clock_gettime(CLOCK_REALTIME, ts);
	ts->tv_sec += ms_from_now / 1000;
	ts->tv_nsec += (ms_from_now % 1000) * 1000000L;
	if (ts->tv_nsec >= 1000000000L)
	{
		ts->tv_sec += 1;
		ts->tv_nsec -= 1000000000L;
	}
}
