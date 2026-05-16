/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:04:13 by dabdulla          #+#    #+#             */
/*   Updated: 2026/05/14 12:34:12 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	monitor_routine(t_philos *philo, t_shared_info *sh)
{
	while (1)
	{
		if (check_table(philo, sh))
			break ;
		usleep(500);
	}
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->shared_info->philo_size == 1)
	{
		print_philo(philo, "has taken a fork");
		ft_usleep(philo->shared_info->time_to_die, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->shared_info->end_mutex);
		if (philo->shared_info->stop_routine)
		{
			pthread_mutex_unlock(&philo->shared_info->end_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->shared_info->end_mutex);
		if (!philo_eat(philo) || !philo_sleep(philo) || !philo_think(philo))
			break ;
		usleep(500);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philos		*philos;
	t_shared_info	shared;
	int				philo_size;

	if (!check_input(ac, av))
		return (1);
	philos = NULL;
	philo_size = ft_atoi(av[1]);
	philos = initialize(&shared, av, philo_size);
	if (!philos)
		return (1);
	if (!create_pthreads(philos, philo_size))
	{
		join_threads(philos, philo_size);
		free_philos(&philos, philo_size);
		return (1);
	}
	monitor_routine(philos, &shared);
	join_threads(philos, philo_size);
	free_philos(&philos, philo_size);
	return (0);
}
