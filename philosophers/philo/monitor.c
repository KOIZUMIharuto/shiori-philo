/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkoizumi <hkoizumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:14 by shiori            #+#    #+#             */
/*   Updated: 2025/02/17 11:10:57 by hkoizumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_philo *philo)
{
    long current_time;
    long since_last_meal_time;
    bool is_dead;
    
    pthread_mutex_lock(philo->state_mutex);
    current_time = get_current_time();
    since_last_meal_time = current_time - philo->last_meal_time;
    is_dead = false;
    // if((since_last_meal_time >= philo->time_to_die) && (!philo->eating))
    if((since_last_meal_time >= philo->time_to_die))
        is_dead = true;
	pthread_mutex_unlock(philo->state_mutex);
    if (is_dead)
    {
        print_status(philo, DIED);
		pthread_mutex_lock(philo->state_mutex);
        *philo->someone_died = true;
		pthread_mutex_unlock(philo->state_mutex);
        return (1);
    }
	return (0);
}



int check_all_philosophers_satisfied(t_philo *philos)
{
    int i;
    int satisfied_count;
    
    i = 0;
    satisfied_count = 0;
    if (philos[0].must_eat_count == -1)
        return (0);
    while (i < philos[0].num_of_philos)
    {
        pthread_mutex_lock(philos[i].state_mutex);
        if (philos[i].eat_count >= philos[i].must_eat_count)
			satisfied_count++;
        pthread_mutex_unlock(philos[i].state_mutex);
        i++;
    }
    if (satisfied_count == philos[0].num_of_philos)
    {
        pthread_mutex_lock(philos[0].state_mutex);
        // *philos->all_satisfied = true;
        *philos->someone_died = true;
        pthread_mutex_unlock(philos[0].state_mutex);        
        return (1);
    }
    return (0);
}
   
void *monitor_routine(void *argv)
{
    t_philo *philos;
    int i;
    
    philos= (t_philo *)argv;
    while (1)
    {
        i = 0;
        while (i < philos[0].num_of_philos)
        {
            if (check_philosopher_death(&philos[i]))
			{
                return (NULL);
			}
            i++;
        }
        if (check_all_philosophers_satisfied(philos))
            return (NULL);
    }
}  



