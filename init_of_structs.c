/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_of_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:20 by luimarti          #+#    #+#             */
/*   Updated: 2026/01/30 21:25:45 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (0);
	data->someone_died = 0;
	data->finished_all_meals = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->finished_mutex, NULL);
	return (1);
}

int	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	if (!init_data(data))
	{
		ft_putstr_fd("❌ Error: Initialization failed!\n", 2);
		return (0);
	}
	i = 0;
	while (i < data->num_philo)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		philos[i].data = data;
		philos[i].last_meal_time = data->start_time;
		i++;
	}
	return (1);
}
