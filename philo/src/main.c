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
		printf("0 1 has taken a fork\n");
		ft_usleep(philo->shared_info->time_to_die, philo);
		printf("%d 1 has died\n", philo->shared_info->time_to_die);
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
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philos		*philos;
	t_shared_info	shared;
	int				philo_size;
	int				i;

	if (!check_input(ac, av))
		return (1);
	philos = NULL;
	i = 0;
	philo_size = ft_atoi(av[1]);
	philos = initialize(&shared, av, philo_size);
	if (!philos)
		return (1);
	create_pthreads(philos, philo_size);
	monitor_routine(philos, &shared);
	while (i < philo_size)
	{
		pthread_join(philos->thread, NULL);
		philos = philos->next;
		i++;
	}
	free_philos(&philos, philo_size);
	return (0);
}
