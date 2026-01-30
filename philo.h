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
#include <stdio.h>      // printf
#include <stdlib.h>     // malloc, free, atoi
#include <unistd.h>     // write, usleep
#include <pthread.h>    // threads y mutex
#include <sys/time.h>   // gettimeofday
#include <string.h>     // memset (opcional)
#include <sys/time.h>

typedef struct s_data
{
    int             num_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_times;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    long            start_time;
}   t_data;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
    long            last_meal_time;
}   t_philo;

//PARSING
int     check_number_args(int argc);
int     parse_args(int argc, char **argv, t_data *data);
int     validate_values(t_data *data);
//BOX_OF_TOOLS
void    ft_putstr_fd(char *s, int fd);
int     ft_atoi(char *str);
//Initialization
int     init_data(t_data *data);
int     init_philos(t_data *data, t_philo *philos);
//Philosopher
void    taking_forks(t_philo *philo);
void    print_action(t_philo *philo, char *action);
void    *philo_routine(void *arg);

long    get_time_ms(void);

#endif
