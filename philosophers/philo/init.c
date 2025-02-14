// init.c
#include "philo.h"

int init_data(t_data *data, int argc, char **argv)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * atoi(argv[1]));
    if (!data->forks)
        return (1);

    if (argc != 5 && argc != 6)
        return (1);

    data->num_philosophers = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);

    if (argc == 6)
    {
        data->must_eat_count = atoi(argv[5]);
        data->all_satisfied = false;
    }
    else 
        data->must_eat_count = -1;

    if (data->num_philosophers <= 0 || data->time_to_die <= 0 ||
        data->time_to_eat <= 0 || data->time_to_sleep <= 0)
        return (1);

    if (argc == 6 && data->must_eat_count <= 0)
        return (1);


    i = 0;
    while (i < data->num_philosophers) {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
            while (--i >= 0) {
                pthread_mutex_destroy(&data->forks[i]);
            }
            return (1);
        }
        i++;
    }
    if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
        return (1);

    data->someone_died = false;

    data->start_time = get_current_time();

    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
        return (1);

    return (0);
}




