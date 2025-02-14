// check_status.c
#include "philo.h"

int check_death(t_philosopher *philo)
{
    long current_time;
    long since_last_meal_time;

    pthread_mutex_lock(&philo->meal_time_mutex);
    current_time = get_current_time();
    since_last_meal_time = current_time - philo->last_meal_time;
    pthread_mutex_unlock(&philo->meal_time_mutex);

    if (since_last_meal_time > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        if (!philo->data->someone_died)
        {
            long death_time = current_time - philo->data->start_time;
            printf("%ld %d died\n", death_time, philo->id + 1);
            philo->data->someone_died = true;
        }
        pthread_mutex_unlock(&philo->data->print_mutex);
        return (1);
    }
    return (0);
}

int check_ate_count(t_philosopher *philo)
{
    int result;
    result = 0;
    pthread_mutex_lock(&philo->eat_count_mutex);
    result = (philo->data->must_eat_count > 0 && 
             philo->eat_count >= philo->data->must_eat_count);
    pthread_mutex_unlock(&philo->eat_count_mutex);
    return result;
}







