/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:43:53 by luimarti          #+#    #+#             */
/*   Updated: 2026/01/30 21:21:14 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	finished_mutex;
	long			start_time;
	int				someone_died;
	t_philo			*philos;
	int				finished_all_meals;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	long			last_meal_time;
}	t_philo;

//PARSING

int		check_number_args(int argc);
int		parse_args(int argc, char **argv, t_data *data);
int		validate_values(t_data *data);

//BOX_OF_TOOLS

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(char *str);

//Initialization

int		init_data(t_data *data);
int		init_philos(t_data *data, t_philo *philos);

//Philosopher

void	taking_forks(t_philo *philo);
void	print_action(t_philo *philo, char *action);
void	routine_for_one(t_philo *philo);
void	starting_routine(t_philo *philo);
void	*preparing_routine(void *arg);

long	get_time_ms(void);
int		check_death(t_data *data, int i);
void	*monitor_death(void *arg);

#endif
