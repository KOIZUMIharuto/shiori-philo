// philosophers.c
#include "philo.h"

void print_status(t_philosopher *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->someone_died)
    {
        long current_time = get_current_time() - philo->data->start_time;
        printf("%ld %d %s\n", current_time, philo->id + 1, status);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}


void *philosopher_routine(void *argv)
{
    t_philosopher *philo = (t_philosopher *)argv;
    t_data *data = philo->data;
    int should_exit = 0;


    while (1)
    {
        pthread_mutex_lock(&data->state_mutex);
        if (data->someone_died || data->all_satisfied)
        {
            should_exit = 1;
        }
        pthread_mutex_unlock(&data->state_mutex);

        if (should_exit == 1)
            return (NULL);  // 早期終了

        thinking(philo);
        
        if (take_forks(philo) == 1)
            return (NULL);  // 哲学者が1人のとき
        
        eating(philo);
        put_down_forks(philo);
        sleeping(philo);
    }

}
