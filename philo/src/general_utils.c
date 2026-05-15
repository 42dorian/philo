/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:31:24 by dabdulla          #+#    #+#             */
/*   Updated: 2026/05/13 15:31:24 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	free_philos(t_philos **head, int philo_size)
{
	t_philos	*curr;
	t_philos	*next;
	int			i;

	if (!head || !(*head))
		return ;
	i = 0;
	curr = *head;
	pthread_mutex_destroy(&curr->shared_info->end_mutex);
	pthread_mutex_destroy(&curr->shared_info->print_mutex);
	while (i < philo_size)
	{
		next = curr->next;
		pthread_mutex_destroy(&curr->meal_mutex);
		pthread_mutex_destroy(&curr->fork);
		free(curr);
		curr = next;
		i++;
	}
	*head = NULL;
}

long	time_to_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_input(int ac, char **av)
{
	int		i;
	long	value;

	i = 1;
	value = 0;
	if (ac < 5 || ac > 6)
		return (printf("Error: Usage: ./philo [n] [ttd] [tte] [tts] (meals)\n"),
			0);
	while (av[i])
	{
		if (!is_num(av[i]) || av[i][0] == '\0')
			return (printf("Error: Argument '%s' must be positive digits\n",
					av[i]), 0);
		value = ft_atoi(av[i]);
		if (value > 2147483647)
			return (printf("Error: Argument '%s' exceeds INT_MAX\n", av[i]), 0);
		if (i == 1 && value < 1)
			return (printf("Error: Must be at least 1 philosopher\n"), 0);
		i++;
	}
	return (1);
}

void	ft_usleep(long ms, t_philos *philo)
{
	long	start_time;

	start_time = time_to_ms();
	while ((time_to_ms() - start_time) < ms)
	{
		pthread_mutex_lock(&philo->shared_info->end_mutex);
		if (philo->shared_info->stop_routine)
		{
			pthread_mutex_unlock(&philo->shared_info->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->shared_info->end_mutex);
		usleep(500);
	}
}

void	join_threads(t_philos *philos, int philo_size)
{
	int	i;

	i = 0;
	while (i < philo_size)
	{
		if (philos->thread)
			pthread_join(philos->thread, NULL);
		philos = philos->next;
		i++;
	}
}
