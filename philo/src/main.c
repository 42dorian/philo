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

int	init_pthreads(void)
{
	return (1);
}

int	main(int ac, char **av)
{
	if (ac > 2 && ac < 7)
		return (1);
	init_pthreads();
	return (0);
}
