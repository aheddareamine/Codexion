/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaheddar <aaheddar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 01:22:27 by aaheddar          #+#    #+#             */
/*   Updated: 2026/08/22 13:35:56 by aaheddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct timeval		t_time;
typedef struct s_simulation	t_simulation;

typedef enum e_scheduler
{
	FIFO,
	EDF
}							t_scheduler;

typedef enum e_coder_state
{
	COMPILING,
	DEBUGGING,
	REFACTORING
}							t_coder_state;

typedef struct s_parameters
{
	int						number_of_coders;
	int						time_to_burnout;
	int						time_to_compile;
	int						time_to_debug;
	int						time_to_refactor;
	int						number_of_compiles_required;
	int						dongle_cooldown;
	t_scheduler				scheduler;
}							t_parameters;

typedef struct s_request
{
	int						coder_index;
	long					seq;
	long					deadline;
}							t_request;

typedef struct s_pqueue
{
	t_request				*data;
	int						size;
	int						capacity;
	t_scheduler				scheduler;
}							t_pqueue;

typedef struct s_dongle
{
	int						index;
	int						taken;
	pthread_mutex_t			lock;
	pthread_cond_t			cond;
	long					available_at;
	long					next_seq;
	t_pqueue				queue;
}							t_dongle;

typedef struct s_coder
{
	int						index;
	int						compile_number;
	t_coder_state			state;
	t_dongle				*left;
	t_dongle				*right;
	t_time					last_compile;
	pthread_t				thread;
	t_simulation			*sim;
}							t_coder;

typedef struct s_simulation
{
	t_parameters			params;
	t_coder					*coders;
	t_dongle				*dongles;
	int						ended;
	pthread_mutex_t			end_lock;
	pthread_mutex_t			print_lock;

}							t_simulation;

t_parameters				*parse(int argc, char **args);
long						gettimestamp(void);
void						set_start_time(void);
long						ms_since_start(t_time *event);
void						future_abstime(long ms_from_now, struct timespec *ts);
int							init_simulation(t_simulation *sim,
								t_parameters *params);
void						destroy_simulation(t_simulation *sim);
void						print_log(t_coder *coder, const char *msg);
int							put_ulong(char *buf, long n);
int							put_str(char *buf, const char *s);
void						log_state(t_coder *coder);
void						log_dongle(t_coder *coder);
void						take_dongles(t_coder *coder);
void						release_dongles(t_coder *coder);
void						acquire_dongle(t_coder *coder, t_dongle *dongle);
void						release_dongle(t_coder *coder, t_dongle *dongle);
void						*coder_routine(void *arg);
void						*monitor_routine(void *arg);
int							is_ended(t_simulation *sim);
void						set_ended(t_simulation *sim);
int							run_simulation(t_simulation *sim);
int							pq_init(t_pqueue *pq, int capacity,
								t_scheduler scheduler);
void						pq_free(t_pqueue *pq);
void						pq_push(t_pqueue *pq, t_request req);
t_request					pq_pop(t_pqueue *pq);
t_request					pq_peek(t_pqueue *pq);
int							req_before(t_pqueue *pq, t_request a, t_request b);
void						pq_swap(t_request *x, t_request *y);
void						pq_sift_up(t_pqueue *pq, int i);
void						pq_sift_down(t_pqueue *pq, int i);

#endif
