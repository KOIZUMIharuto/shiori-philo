// main.c

#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    if (init_data(&data, argc, argv) != 0)
        return(1);

    t_philosopher *philosophers = malloc(sizeof(t_philosopher) * data.num_philosophers);
    int i;
    if (!philosophers) {
        return 1;
    }

    data.philosophers = philosophers;


    i = 0;
    while(i < data.num_philosophers)
    {
        philosophers[i].id = i;
        philosophers[i].eat_count = 0;
        philosophers[i].last_meal_time = get_current_time();
        philosophers[i].data = &data;

            if (pthread_mutex_init(&philosophers[i].meal_time_mutex, NULL) != 0 ||
        pthread_mutex_init(&philosophers[i].eat_count_mutex, NULL) != 0)
    {
        // エラー処理
        while (--i >= 0)
        {
            pthread_mutex_destroy(&philosophers[i].meal_time_mutex);
            pthread_mutex_destroy(&philosophers[i].eat_count_mutex);
        }
        cleanup_resources(&data);
        return (1);
    }

        if (pthread_create(&philosophers[i].thread, NULL,
                          philosopher_routine, &philosophers[i]) != 0)
        {
            while (--i >= 0)
                pthread_join(philosophers[i].thread, NULL);
            cleanup_resources(&data);   
            return (1);
        }
        i++;
    }

    if (pthread_create(&data.monitor, NULL, monitor_routine, philosophers) != 0)
    {
        cleanup_resources(&data);
        error_exit("Monitor thread creation failed");
    }

    i=0;
    while(i < data.num_philosophers)
    {
        pthread_join(philosophers[i].thread, NULL);
        printf("Philosopher %d final eat count: %d\n", i + 1, philosophers[i].eat_count);
        i++;
    }
    // シミュレーションの終了待ち
    i=0;
    pthread_join(data.monitor, NULL);
    cleanup_resources(&data);

    return (0);
}