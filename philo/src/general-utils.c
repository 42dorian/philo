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

int	check_input(int ac)
{
	return (1);
}
