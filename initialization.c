/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:20 by luimarti          #+#    #+#             */
/*   Updated: 2026/01/18 15:51:12 by luimarti         ###   ########.fr       */
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
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
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
		philos[i].id = i;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		philos[i].data = data;
		i++;
	}
	printf ("Initialization completed!\n");
	return (1);
}
