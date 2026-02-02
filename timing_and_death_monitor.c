/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing_and_death_monitor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:16:30 by lucho             #+#    #+#             */
/*   Updated: 2026/02/02 00:07:16 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_death(t_data *data, int i)
{
	long	last_meal;
	long	now;
	long	time_elapsed;

	pthread_mutex_lock(&data->meal_mutex);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->meal_mutex);
	now = get_time_ms();
	time_elapsed = now - last_meal;
	if (time_elapsed > data->time_to_die)
	{
		print_action(&data->philos[i], "died");
		data->someone_died = 1;
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
