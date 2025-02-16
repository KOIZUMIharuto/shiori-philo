/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:31:05 by shiori            #+#    #+#             */
/*   Updated: 2025/02/17 05:06:25 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_create(t_program *program)
{
	pthread_t	monitor;
	int			i;

	pthread_create(&monitor, NULL,monitor_routine, program->philos);
	i = 0;
	while (i < program->num_of_philos)
	{
		pthread_create(&program->philos[i].thread, NULL,philo_routine,
				&program->philos[i]);
		i++;
	}
	i = 0;
	pthread_join(monitor,NULL);
    i = 0;
	while (i < program->num_of_philos)
	{
		pthread_join(program->philos[i].thread,NULL);
		i++;
	}
}


int should_stop_simulation(t_philo *philo)
{
    pthread_mutex_lock(philo->state_mutex);
    if (*philo->someone_died || *philo->all_satisfied)
        return (pthread_mutex_unlock(philo->state_mutex), 1);
    pthread_mutex_unlock(philo->state_mutex);
    return (0);
}

void print_status(t_philo *philo,const char *status)
{
    pthread_mutex_lock(philo->print_mutex);
    if (!should_stop_simulation(philo))
       printf("%ld %d %s\n", get_current_time() - philo->start_time, philo->id, status);
    pthread_mutex_unlock(philo->print_mutex);
}

void *philo_routine(void *argv)
{
    t_philo *philo;
    
    philo= (t_philo *)argv;
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (!should_stop_simulation(philo))
    {
        take_forks(philo);
        eating(philo);
        put_down_forks(philo);
        sleeping(philo);
        thinking(philo);
    }
    pthread_exit(NULL);
}