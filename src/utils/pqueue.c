/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pqueue.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:00:00 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/23 20:20:44 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/core.h"

int	pq_init(t_pqueue *pq, int capacity, t_scheduler scheduler)
{
	pq->data = malloc(sizeof(t_request) * capacity);
	if (!pq->data)
		return (0);
	pq->size = 0;
	pq->capacity = capacity;
	pq->scheduler = scheduler;
	return (1);
}

void	pq_free(t_pqueue *pq)
{
	free(pq->data);
	pq->data = NULL;
}

void	pq_push(t_pqueue *pq, t_request req)
{
	if (pq->size >= pq->capacity)
		return ;
	pq->data[pq->size] = req;
	pq->size++;
	pq_sift_up(pq, pq->size - 1);
}

t_request	pq_pop(t_pqueue *pq)
{
	t_request	top;

	if (pq->size == 0)
		return (pq_peek(pq));
	top = pq->data[0];
	pq->size--;
	pq->data[0] = pq->data[pq->size];
	pq_sift_down(pq, 0);
	return (top);
}

t_request	pq_peek(t_pqueue *pq)
{
	t_request	empty;

	if (pq->size == 0)
	{
		empty.coder_index = -1;
		empty.seq = -1;
		empty.deadline = 0;
		return (empty);
	}
	return (pq->data[0]);
}
