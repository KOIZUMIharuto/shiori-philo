/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:21:20 by shiori            #+#    #+#             */
/*   Updated: 2025/02/17 04:49:03 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"


typedef struct s_philo
{
    pthread_t		thread;
    int             id;
    bool             eating;
    int             eat_count;
    long            last_meal_time;
    long            start_time;
    bool            *someone_died;
    bool            *all_satisfied;
    int				num_of_philos;
    long			time_to_die;
    long			time_to_eat;
    long			time_to_sleep;
    int             must_eat_count;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t *state_mutex;
} t_philo;

typedef struct s_program {
    int				num_of_philos;
    bool someone_died;
    bool all_satisfied;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t state_mutex;
    t_philo *philos;
} t_program;

int should_stop_simulation(t_philo *philo);
void   init_program(t_program *program);
void	init_philos(t_philo *philos, t_program *program, char **argv);
void	thread_create(t_program *program);
void    *philo_routine(void *arg);
void    *monitor_routine(void *arg);
void    take_forks(t_philo *philo);
void    eating(t_philo *philo);
void    sleeping(t_philo *philo);
void    thinking(t_philo *philo);
void    put_down_forks(t_philo *philo);
long    get_current_time(void);
void    print_status(t_philo *philo, const char *status);
int     ft_atoi(const char *str);
void    ft_usleep(long milliseconds);
void cleanup_resources(char *str, t_program *program);



#endif