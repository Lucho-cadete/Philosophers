/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_and_death_monitor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:16:30 by lucho             #+#    #+#             */
/*   Updated: 2026/02/15 16:41:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	nap_sleep(long duration, t_data *data)
{
	long	start;

	start = get_time_ms();
	while (!is_dead(data))
	{
		if (get_time_ms() - start >= duration)
			break ;
		usleep(500);
	}
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_dead(t_data *data)
{
	int	died;

	pthread_mutex_lock(&data->print_mutex);
	died = data->someone_died;
	pthread_mutex_unlock(&data->print_mutex);
	return (died);
}

int	check_death(t_data *data, int i)
{
	long	last_meal;
	long	now;
	long	time_elapsed;

	if (data->must_eat_times != -1
		&& data->philos[i].meals_eaten >= data->must_eat_times)
		return (0);
	pthread_mutex_lock(&data->meal_mutex);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->meal_mutex);
	now = get_time_ms();
	time_elapsed = now - last_meal;
	if (time_elapsed > data->time_to_die)
	{
		print_action(&data->philos[i], "died");
		pthread_mutex_lock(&data->print_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *) arg;
	while (1)
	{
		pthread_mutex_lock(&data->finished_mutex);
		if (data->finished_all_meals == data->num_philo)
		{
			pthread_mutex_unlock(&data->finished_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->finished_mutex);
		i = 0;
		while (i < data->num_philo)
		{
			if (check_death(data, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
