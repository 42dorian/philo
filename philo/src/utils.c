/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:54:44 by dabdulla          #+#    #+#             */
/*   Updated: 2026/05/11 17:04:05 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philos **head, int philo_size)
{
	t_philos	*curr;
	t_philos    *next;
	int i;

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

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void print_philo(t_philos *philo, char *msg)
{
    long time;
    time += philo->shared_info->start_time - time_to_ms();
    printf("%lu %d %s\n", time, philo->id, msg);
}

int check_input(int ac)
{
    //properly check input
    return 1;
}
