/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:02:06 by lucho             #+#    #+#             */
/*   Updated: 2026/01/25 16:04:43 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	int		counter;
	t_philo	*philo;

	philo = (t_philo *) arg;
	counter = 0;
	while (counter < 5)
	{
		printf ("Philosopher %i is thinking.\n", philo->id);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			printf ("Philosopher %i has taken a fork.\n", philo->id);
			pthread_mutex_lock(philo->right_fork);
			printf ("Philosopher %i has taken a fork.\n", philo->id);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			printf ("Philosopher %i has taken a fork.\n", philo->id);
			pthread_mutex_lock(philo->left_fork);
			printf ("Philosopher %i has taken a fork.\n", philo->id);
		}
		printf ("Philosopher %i is eating.\n", philo->id);
		usleep (philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf ("Philosopher %i is sleeping.\n", philo->id);
		usleep (philo->data->time_to_sleep * 1000);
		counter++;
	}
	return (NULL);
}
