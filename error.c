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

    for (i = 0; i < data->num_philosophers; i++)
        pthread_mutex_destroy(&data->forks[i]);

    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
    pthread_mutex_destroy(&data->meal_mutex);
    pthread_mutex_destroy(&data->state_mutex);
}

