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
