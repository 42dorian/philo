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

int	philo_eat(t_philos *philo)
{
	if (philo->shared_info->stop_routine == 1 || philo->is_done)
		return (0);
	pthread_mutex_lock(&philo->shared_info->end_mutex);
	if ((time_to_ms() - philo->last_meal) >= philo->shared_info->time_to_die)
	{
		if (philo->shared_info->stop_routine == 0)
		{
			philo->shared_info->stop_routine = 1;
			print_philo(philo, "has died");
		}
		pthread_mutex_unlock(&philo->shared_info->end_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared_info->end_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	print_philo(philo, "is eating");
	philo->meal_count++;
	philo->last_meal = time_to_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep((long)philo->shared_info->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->next_fork);
	return (1);
}

int	philo_sleep(t_philos *philo)
{
	if (philo->shared_info->stop_routine == 1 || philo->is_done)
		return (0);
	ft_usleep((long)philo->shared_info->time_to_sleep);
	print_philo(philo, "is sleeping");
	return (1);
}

int	philo_think(t_philos *philo)
{
	if (philo->shared_info->stop_routine == 1 || philo->is_done)
		return (0);
	print_philo(philo, "is thinking");
	return (1);
}
