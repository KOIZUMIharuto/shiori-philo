// error.c
#include "philo.h"

// エラーメッセージを表示して終了
void error_exit(char *message)
{
    printf("Error: %s\n", message);
    exit(1);
}

// リソースを解放する関数
void cleanup_resources(t_data *data)
{
    int i;
    i = 0;
    while (i < data->num_philosophers) {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philosophers[i].meal_time_mutex);
        pthread_mutex_destroy(&data->philosophers[i].eat_count_mutex);
        i++;
    }
    free(data->forks);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->state_mutex);
    free(data->philosophers);
}

