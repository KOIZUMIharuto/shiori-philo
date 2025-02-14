// philosopher_routine.c
#include "philo.h"

void thinking(t_philosopher *philo)
{
    print_status(philo, THINKING);
}

int take_forks(t_philosopher *philo)
{
    int right_fork, left_fork;
    
    if (philo->data->num_philosophers == 1)
    {
        pthread_mutex_lock(&philo->data->forks[0]);
        print_status(philo, FORK_TAKEN);
        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(&philo->data->forks[0]);
        return (1);
    }

    right_fork = philo->id;
    left_fork = (philo->id + 1) % philo->data->num_philosophers;

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks[right_fork]);
        print_status(philo, FORK_TAKEN);
        pthread_mutex_lock(&philo->data->forks[left_fork]);
        print_status(philo, FORK_TAKEN);
    }
    else
    {
        usleep(200);
        pthread_mutex_lock(&philo->data->forks[right_fork]);
        print_status(philo, FORK_TAKEN);
        pthread_mutex_lock(&philo->data->forks[left_fork]);
        print_status(philo, FORK_TAKEN);
    }
    return (0);
}

void eating(t_philosopher *philo)
{
    print_status(philo, EATING);
    
    pthread_mutex_lock(&philo->meal_time_mutex);  // 追加が必要
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->meal_time_mutex);
    pthread_mutex_lock(&philo->eat_count_mutex);  // 追加が必要
    philo->eat_count++;
    pthread_mutex_unlock(&philo->eat_count_mutex);

    // デバッグ出力
    // printf("Philosopher %d eat count: %d\n", philo->id + 1, philo->eat_count);

    // 指定された回数食事したら満足フラグを立てる
    // if (philo->data->must_eat_count > 0 && 
    //     philo->eat_count >= philo->data->must_eat_count)
    // {
    //     philo->is_satisfied = true;
    // }
    usleep(philo->data->time_to_eat * 1000);

}

void put_down_forks(t_philosopher *philo)
{
    int left_fork = philo->id;
    int right_fork = (philo->id + 1) % philo->data->num_philosophers;

    pthread_mutex_unlock(&philo->data->forks[left_fork]);
    pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void sleeping(t_philosopher *philo)
{
    print_status(philo, SLEEPING);
    usleep(philo->data->time_to_sleep * 1000);
}

