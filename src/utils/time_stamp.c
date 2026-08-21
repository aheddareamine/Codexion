/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 01:22:35 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/21 01:22:36 by aaheddar         ###   ########.fr       */
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
