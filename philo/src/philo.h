/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:06:05 by dabdulla          #+#    #+#             */
/*   Updated: 2026/05/06 17:06:28 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_shared_info	t_shared_info;
typedef struct s_philos			t_philos;

typedef struct s_shared_info
{
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							max_meals;
	int							stop_routine;
	long						start_time;
	pthread_mutex_t				end_mutex;
	pthread_mutex_t				print_mutex;
}								t_shared_info;

typedef struct s_philos
{
	int							id;
	int							meal_count;
	int							is_done;
	long						last_meal;
	pthread_t					thread;
	pthread_mutex_t				fork;
	pthread_mutex_t				*next_fork;
	pthread_mutex_t				meal_mutex;
	t_shared_info				*shared_info;
	t_philos					*next;
}								t_philos;

int								ft_atoi(char *nptr);
void							*ft_memset(void *s, int c, size_t n);
void							ft_bzero(void *s, size_t n);
void							*ft_calloc(size_t nmemb, size_t size);
long							time_to_ms(void);
void							free_philos(t_philos **philo, int philo_size);
int								is_num(char *str);
t_philos						*init_philos(int philo_size,
									t_shared_info *shared_info);
void							link_forks(int philo_size, t_philos *philo);
void							print_philo(t_philos *philo, char *msg);
void							ft_usleep(long ms);
int								philo_eat(t_philos *philo);
int								philo_sleep(t_philos *philo);
int								philo_think(t_philos *philo);
int								check_input(int ac, char **av);
void							*philo_routine(void *arg);
void							create_pthreads(t_philos *philo,
									int philo_size);
int init_shared(t_shared_info *shared, char **av);
int args_to_shared_info(t_shared_info *shared, char **av);
#endif
