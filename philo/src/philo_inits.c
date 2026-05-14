/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 14:37:12 by dabdulla          #+#    #+#             */
/*   Updated: 2026/05/14 14:37:12 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_shared(t_shared_info *shared, char **av)
{
    shared = ft_calloc(sizeof(t_shared_info), 1);
    if (!shared)
        return (0);
    args_to_shared_info(shared, av);
    pthread_mutex_init(&shared->end_mutex, NULL);
    pthread_mutex_init(&shared->print_mutex, NULL);
    return (1);
}

t_philos	*init_philos(int philo_size, t_shared_info *shared_info)
{
	int			i;
	t_philos	*head;
	t_philos	*curr;
	t_philos	*new;

	head = NULL;
	curr = NULL;
	i = -1;
	while (++i < philo_size)
	{
		new = ft_calloc(sizeof(t_philos), 1);
		if (!new)
			return (free_philos(&head, i), NULL);
		new->id = i + 1;
		new->shared_info = shared_info;
		pthread_mutex_init(&new->meal_mutex, NULL);
		pthread_mutex_init(&new->fork, NULL);
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
	}
	curr->next = head;
	return (head);
}

void	create_pthreads(t_philos *philo, int philo_size)
{
	int	i;

	i = 0;
	while (i < philo_size)
	{
		pthread_create(&philo->thread, NULL, philo_routine, philo);
		philo = philo->next;
		i++;
	}
}
