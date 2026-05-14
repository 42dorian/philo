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
	int	i;

	i = 0;
	if (ac < 2 || ac > 6)
		return (0);
	if (ft_atoi(av[1]) < 1)
	{
		printf("Error:\nMust be at least 1 philo\n");
		return (0);
	}
	while (av[i])
	{
		if (!is_num(av[i]))
			return (printf("Error:\nArguments must be all digits!\n"), 1);
		i++;
	}
	return (1);
}

void	ft_usleep(long ms)
{
	long	start_time;

	start_time = time_to_ms();
	while ((time_to_ms() - start_time) < ms)
		usleep(500);
}
