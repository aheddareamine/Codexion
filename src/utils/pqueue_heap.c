/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue_heap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:00:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/23 20:21:00 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

int	req_before(t_pqueue *pq, t_request a, t_request b)
{
	if (pq->scheduler == EDF)
	{
		if (a.deadline != b.deadline)
			return (a.deadline < b.deadline);
		return (a.seq < b.seq);
	}
	return (a.seq < b.seq);
}

void	pq_swap(t_request *x, t_request *y)
{
	t_request	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void	pq_sift_up(t_pqueue *pq, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!req_before(pq, pq->data[i], pq->data[parent]))
			break ;
		pq_swap(&pq->data[i], &pq->data[parent]);
		i = parent;
	}
}

void	pq_sift_down(t_pqueue *pq, int i)
{
	int	best;
	int	l;
	int	r;

	best = i;
	l = 2 * i + 1;
	r = 2 * i + 2;
	while ((l < pq->size && req_before(pq, pq->data[l], pq->data[best]))
		|| (r < pq->size && req_before(pq, pq->data[r], pq->data[best])))
	{
		if (r < pq->size && req_before(pq, pq->data[r], pq->data[l]))
			best = r;
		else
			best = l;
		pq_swap(&pq->data[i], &pq->data[best]);
		i = best;
		best = i;
		l = 2 * i + 1;
		r = 2 * i + 2;
	}
}
