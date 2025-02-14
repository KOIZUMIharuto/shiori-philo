// monitor.c
#include "philo.h"

void *monitor_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo[0].data;
    int i;
    int satisfied_count;

    while (1)
    {
        i=0;
        satisfied_count = 0;
        while (i < data->num_philosophers)
        {
            if (check_death(&philo[i]))
                return (NULL);
            if (check_ate_count(&philo[i]))
                satisfied_count++;
            i++;
        }
        if (satisfied_count == data->num_philosophers)
        {
            pthread_mutex_lock(&data->print_mutex);
            data->all_satisfied = true;
            // printf("全ての哲学者が指定回数の食事を終えました。\n");
            pthread_mutex_unlock(&data->print_mutex);
            return (NULL);
        }
    }
}

