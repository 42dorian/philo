/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo-utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:46:36 by dabdulla          #+#    #+#             */
/*   Updated: 2026/05/13 12:46:36 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_to_shared_info(t_shared_info *shared, char **av)
{
	shared->philo_size = ft_atoi(av[1]);
	shared->time_to_die = ft_atoi(av[2]);
	shared->time_to_eat = ft_atoi(av[3]);
	shared->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		shared->max_meals = ft_atoi(av[5]);
	else
		shared->max_meals = -1;
	shared->stop_routine = 0;
	return (1);
}

void	link_forks(int philo_size, t_philos *philo)
{
	int			i;
	t_philos	*curr;

	curr = philo;
	i = 0;
	while (i < philo_size)
	{
		curr->next_fork = &curr->next->fork;
		curr = curr->next;
		i++;
	}
}

void	grab_forks(t_philos *philo)
{
	if (philo->is_done)
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		print_philo(philo, "has taken a fork");
		pthread_mutex_lock(philo->next_fork);
		print_philo(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->next_fork);
		print_philo(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork);
		print_philo(philo, "has taken a fork");
	}
}

void	print_philo(t_philos *philo, char *msg)
{
	long	time;

	if (philo->is_done)
		return ;
	time = 0;
	time += time_to_ms() - philo->shared_info->start_time;
	pthread_mutex_lock(&philo->shared_info->print_mutex);
	if (philo->shared_info->stop_routine == 0)
		printf("%lu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->shared_info->print_mutex);
}

int	check_table(t_philos *p, t_shared_info *sh)
{
	int	philos_full;
	int	i;

	philos_full = 0;
	i = 0;
	while (i < sh->philo_size)
	{
		if (has_died(p))
			return (1);
		pthread_mutex_lock(&p->meal_mutex);
		if (sh->max_meals != -1 && p->meal_count >= sh->max_meals)
			philos_full++;
		pthread_mutex_unlock(&p->meal_mutex);
		p = p->next;
		i++;
	}
	if (sh->max_meals != -1 && philos_full == sh->philo_size)
	{
		pthread_mutex_lock(&sh->end_mutex);
		sh->stop_routine = 1;
		pthread_mutex_unlock(&sh->end_mutex);
		return (1);
	}
	return (0);
}
