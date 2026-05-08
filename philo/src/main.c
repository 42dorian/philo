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

void	*billion(void *a);

int	main(int ac, char **av)
{
	pthread_t	thread1;
	pthread_t	thread2;

	if (ac > 2 && ac < 7)
		return (1);
	pthread_create(&thread1, NULL, billion, NULL);
	pthread_create(&thread2, NULL, billion, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return (0);
}

void	*billion(void *a)
{
	int	i;

	i = 0;
	while (i < 1000000000)
		i++;
	return (NULL);
}
