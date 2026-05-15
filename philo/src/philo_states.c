/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:46:49 by dabdulla          #+#    #+#             */
/*   Updated: 2026/05/13 12:46:49 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	has_died(t_philos *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = time_to_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->shared_info->end_mutex);
	if (last_meal >= philo->shared_info->time_to_die)
	{
		if (philo->shared_info->stop_routine == 0)
		{
			philo->shared_info->stop_routine = 1;
			pthread_mutex_lock(&philo->shared_info->print_mutex);
			printf("%lu %d has died\n", time_to_ms()
				- philo->shared_info->start_time, philo->id);
			pthread_mutex_unlock(&philo->shared_info->print_mutex);
		}
		pthread_mutex_unlock(&philo->shared_info->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared_info->end_mutex);
	return (0);
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

int	philo_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared_info->end_mutex);
	if (philo->shared_info->stop_routine == 1)
	{
		pthread_mutex_unlock(&philo->shared_info->end_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared_info->end_mutex);
	grab_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time_to_ms();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_philo(philo, "is eating");
	ft_usleep((long)philo->shared_info->time_to_eat, philo);
	release_forks(philo);
	return (1);
}

int	philo_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared_info->end_mutex);
	if (philo->shared_info->stop_routine == 1)
	{
		pthread_mutex_unlock(&philo->shared_info->end_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared_info->end_mutex);
	print_philo(philo, "is sleeping");
	ft_usleep((long)philo->shared_info->time_to_sleep, philo);
	return (1);
}

int	philo_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared_info->end_mutex);
	if (philo->shared_info->stop_routine == 1)
	{
		pthread_mutex_unlock(&philo->shared_info->end_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared_info->end_mutex);
	print_philo(philo, "is thinking");
	return (1);
}
