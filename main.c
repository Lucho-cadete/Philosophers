/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:49:45 by luimarti          #+#    #+#             */
/*   Updated: 2026/01/30 21:25:00 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	int			i;
	pthread_t	monitor;

	i = -1;
	if (!parse_args(argc, argv, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	philos = malloc (sizeof(t_philo) * data.num_philo);
	if (!philos)
		return (1);
	data.start_time = get_time_ms();
	if (!init_philos(&data, philos))
		return (1);
	data.philos = philos;
	pthread_create(&monitor, NULL, monitor_death, &data);
	while (++i < data.num_philo)
		pthread_create(&philos[i].thread, NULL, preparing_routine, &philos[i]);
	i = -1;
	while (++i < data.num_philo)
		pthread_join(philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
