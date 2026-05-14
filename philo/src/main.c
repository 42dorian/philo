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

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
        if(!philo_eat(philo))
            break;
        if (!philo_sleep(philo))
            break;
        if (!philo_think(philo))
            break;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
    t_philos *philos;
    t_shared_info *shared;

    philos = NULL;
    shared = NULL;
	if (!check_input(ac, av))
		return (1);
	if (!init_shared(shared, av))
        return (1);
	if (!init_philos(ft_atoi(av[1]), shared))
	    return (1);
	create_pthreads(philos, ft_atoi(av[1]));
	return (0);
}
