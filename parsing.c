/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:13:34 by luimarti          #+#    #+#             */
/*   Updated: 2026/01/18 13:08:31 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number_args(int argc)
{
	if (argc != 5 && argc != 6)
		return (0);
	return (1);
}

int	validate_values(t_data *data)
{
	if (data->num_philo <= 0)
		return (0);
	if (data->time_to_die <= 0)
		return (0);
	if (data->time_to_eat <= 0)
		return (0);
	if (data->time_to_sleep <= 0)
		return (0);
	if (data->must_eat_times == 0)
		return (0);
	return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (!check_number_args(argc))
	{
		ft_putstr_fd("❌ Error: Incorrect number of args.\n", 2);
		return (0);
	}
	data->num_philo = ft_atoi (argv[1]);
	data->time_to_die = ft_atoi (argv[2]);
	data->time_to_eat = ft_atoi (argv[3]);
	data->time_to_sleep = ft_atoi (argv[4]);
	if (argc == 6)
		data->must_eat_times = ft_atoi (argv[5]);
	else
		data->must_eat_times = -1;
	if (!validate_values(data))
	{
		ft_putstr_fd("❌ Error: Inappropriate values.\n", 2);
		return (0);
	}
	return (1);
}
