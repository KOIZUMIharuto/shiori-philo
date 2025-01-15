// monitor.c
#include "philo.h"

// 監視用スレッドの実装


void *monitor_routine(void *arg)
{
    t_philosopher *philosophers = (t_philosopher *)arg;
    t_data *data = philosophers[0].data;
    int i;

    while (1)
    {
        pthread_mutex_lock(&data->death_mutex);
        if (data->someone_died || data->all_satisfied)
        {
            pthread_mutex_unlock(&data->death_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&data->death_mutex);

        // 全員が食事を終えたかチェック
        if (check_all_ate_must_eat_count(philosophers))
        {
            return (NULL);
        }

        // 死亡チェック
        for (i = 0; i < data->num_philosophers; i++)
        {
            if (check_death(&philosophers[i]))
            {
                return (NULL);
            }
        }

        usleep(1000);  // チェック間隔
    }
}

