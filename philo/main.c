// main.c

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]
// last meal or the beginning of the simulation, they die.
// number_of_times_each_philosopher_must_eat
// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking


// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock

// ◦ timestamp_in_ms X died
#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    t_philosopher philosophers[MAX_PHILOSOPHERS];  // スタック上に確保
    int i;
    
    if (init_data(&data, argc, argv) != 0)
        return(1);

      data.philosophers = philosophers;

    // 哲学者の初期化とシミュレーション開始

    i = 0;
    printf("%d\n",data.num_philosophers);
    while(i < data.num_philosophers)
    {
        philosophers[i].id = i;
        philosophers[i].eat_count = 0;
        philosophers[i].is_satisfied = false;
        philosophers[i].last_meal_time = get_current_time();
        philosophers[i].data = &data;

        if (pthread_create(&philosophers[i].thread, NULL,
                          philosopher_routine, &philosophers[i]) != 0)
        {
            // エラー発生時は既に作成したスレッドを終了
            while (--i >= 0)
                pthread_join(philosophers[i].thread, NULL);
            // return (1);
        }
        i++;
    }
    // if (initialize_philosophers(&data,data.philosophers) != 0)
    // {
    //     cleanup_resources(&data);
    //     return(1);
    // }

    // main.c - 修正後
    if (pthread_create(&data.monitor, NULL, monitor_routine, philosophers) != 0)
    {
        cleanup_resources(&data);
        error_exit("Monitor thread creation failed");
    }

    // シミュレーションの終了待ち
    i=0;
    while(i < data.num_philosophers)
    {
        pthread_join(philosophers[i].thread, NULL);
        printf("Philosopher %d final eat count: %d\n", i + 1, philosophers[i].eat_count);
        i++;
    }
    // シミュレーションの終了待ち
    i=0;
    while(i < data.num_philosophers)
    {
        pthread_join(philosophers[i].thread, NULL);
        i++;
    }
    pthread_join(data.monitor, NULL);
    cleanup_resources(&data);


    return (0);
}