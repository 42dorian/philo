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

void	grab_forks(t_philos *philo)
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

void	print_philo(t_philos *philo, char *msg)
{
	long	time;

	time += philo->shared_info->start_time - time_to_ms();
	printf("%lu %d %s\n", time, philo->id, msg);
}
