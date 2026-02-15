/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_cleaning.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:21:07 by luimarti          #+#    #+#             */
/*   Updated: 2026/02/08 17:00:02 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_and_clean(t_data *data, t_philo *philos, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->finished_mutex);
	free(data->forks);
	free(philos);
}
