/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:11 by shiori            #+#    #+#             */
/*   Updated: 2025/02/16 17:07:23 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// philo_routine.c
#include "philo.h"

void thinking(t_philo *philo)
{
    print_status(philo, THINKING);
}
void sleeping(t_philo *philo)
{
    print_status(philo, SLEEPING);
    ft_usleep(philo->time_to_sleep);
}

void take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, FORK_TAKEN);
    if (philo->num_of_philos == 1)
    {
        ft_usleep(philo->time_to_die);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, FORK_TAKEN);
}

void eating(t_philo *philo)
{
    pthread_mutex_lock(philo->state_mutex);
    philo->eating = true;
    philo->last_meal_time = get_current_time();
    philo->eat_count++;
    pthread_mutex_unlock(philo->state_mutex);
    print_status(philo, EATING);
    ft_usleep(philo->time_to_eat);
    pthread_mutex_lock(philo->state_mutex);
    philo->eating = false;
    pthread_mutex_unlock(philo->state_mutex);
}

void put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
