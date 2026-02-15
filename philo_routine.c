/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:02:06 by lucho             #+#    #+#             */
/*   Updated: 2026/02/15 16:49:31 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
}

void	print_action(t_philo *philo, char *action)
{
	long	now;
	long	elapsed;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	now = get_time_ms();
	elapsed = now - philo->data->start_time;
	printf("%li %i %s\n", elapsed, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	routine_for_one(t_philo *philo)
{
	print_action(philo, "is thinking");
	print_action(philo, "has taken a fork");
	nap_sleep(philo->data->time_to_die, philo->data);
}

void	philo_routine(t_philo *philo)
{
	print_action(philo, "is thinking");
	taking_forks(philo);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_action(philo, "is eating");
	nap_sleep(philo->data->time_to_eat, philo->data);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (is_dead(philo->data))
		return ;
	print_action(philo, "is sleeping");
	nap_sleep(philo->data->time_to_sleep, philo->data);
}

void	*preparing_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->data->num_philo == 1)
	{
		routine_for_one(philo);
		return (NULL);
	}
	while (!is_dead(philo->data))
	{
		philo_routine(philo);
		if (philo->meals_eaten == philo->data->must_eat_times
			&& philo->data->must_eat_times != -1)
		{
			pthread_mutex_lock(&philo->data->finished_mutex);
			philo->data->finished_all_meals++;
			pthread_mutex_unlock(&philo->data->finished_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
