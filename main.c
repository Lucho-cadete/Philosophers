/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:49:45 by luimarti          #+#    #+#             */
/*   Updated: 2026/01/18 15:51:36 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (!parse_args(argc, argv, &data))
		return (1);
	philos = malloc (sizeof(t_philo) * data.num_philo);
	if (!philos)
		return (1);
	if (!init_philos(&data, philos))
		return (1);
	printf ("Numero de filosofos: %d\n", data.num_philo);
	printf ("Time to die: %d\n", data.time_to_die);
	printf ("Time to eat: %d\n", data.time_to_eat);
	printf ("Time to sleep: %d\n", data.time_to_sleep);
	if (argc == 6)
		printf ("Number of times eating: %d\n", data.must_eat_times);
	return (0);
}
