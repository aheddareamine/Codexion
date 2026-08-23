/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:30:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/23 20:19:10 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

int	put_ulong(char *buf, long n)
{
	char	tmp[24];
	int		i;
	int		len;

	if (n == 0)
	{
		buf[0] = '0';
		return (1);
	}
	i = 0;
	while (n > 0)
	{
		tmp[i++] = '0' + (n % 10);
		n /= 10;
	}
	len = 0;
	while (i > 0)
		buf[len++] = tmp[--i];
	return (len);
}

int	put_str(char *buf, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		buf[i] = s[i];
		i++;
	}
	return (i);
}
