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

int main(int argc, char **argv)
{
    t_data  data;
    t_philo *philos;
    int     i;
    if (!parse_args(argc, argv, &data))
        return (1);
    philos = malloc (sizeof(t_philo) * data.num_philo);
    if (!philos)
        return (1);
    if (!init_philos(&data, philos))
        return (1);
    data.start_time = get_time_ms();
    i = 0;
    while (i < data.num_philo)
    {
        pthread_create (&philos[i].thread, NULL, philo_routine, &philos[i]);
        i++;
    }
    i = 0;
    while (i < data.num_philo)
    {
        pthread_join (philos[i].thread, NULL);
        i++;
    }
    return (0);
}
