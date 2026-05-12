/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:04:13 by dabdulla          #+#    #+#             */
/*   Updated: 2026/05/06 17:05:26 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

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

void grab_forks(t_philos *philo)
{
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

int	main(int ac, char **av)
{
	int	i;

	if (ac < 2 || ac > 6)
		return (1);
	i = 1;
	while (av[i])
	{
		if (!is_num(av[i]))
			return (printf("wrong"), 1);
		i++;
	}
	return (0);
}
