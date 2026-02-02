/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:02:06 by lucho             #+#    #+#             */
/*   Updated: 2026/02/02 00:07:26 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}

void	print_action(t_philo *philo, char *action)
{
	long	now;
	long	elapsed;

	pthread_mutex_lock(&philo->data->print_mutex);
	now = get_time_ms();
	elapsed = now - philo->data->start_time;
	printf("%li %i %s\n", elapsed, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	routine_for_one(t_philo *philo)
{
	if (philo->data->someone_died)
		return ;
	print_action(philo, "is thinking");
	if (philo->data->someone_died)
		return ;
	print_action(philo, "has taken a fork");
	while (!philo->data->someone_died)
		usleep(1000);
	return ;
}

void	philo_routine(t_philo *philo)
{
	print_action(philo, "is thinking");
	taking_forks(philo);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->data->someone_died)
		return ;
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	*preparing_routine(void *arg)
{
	int		counter;
	t_philo	*philo;

	philo = (t_philo *) arg;
	counter = 0;
	if (philo->data->num_philo == 1)
	{
		routine_for_one(philo);
		return (NULL);
	}
	while ((counter < philo->data->must_eat_times
			|| philo->data->must_eat_times == -1)
		&& !philo->data->someone_died)
	{
		philo_routine(philo);
		counter++;
	}
	if (counter == philo->data->must_eat_times
		&& philo->data->must_eat_times != -1)
	{
		pthread_mutex_lock(&philo->data->finished_mutex);
		philo->data->finished_all_meals++;
		pthread_mutex_unlock(&philo->data->finished_mutex);
	}
	return (NULL);
}
