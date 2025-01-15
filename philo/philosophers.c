// philosophers.c
#include "philo.h"

// 状態出力用の関数（排他制御付き）
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

    while (1)
    {
        pthread_mutex_lock(&data->death_mutex);
        if (data->someone_died || data->all_satisfied)
        {
            pthread_mutex_unlock(&data->death_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&data->death_mutex);

        // 指定回数食事済みの場合は終了
        if (philo->eat_count >= data->must_eat_count && data->must_eat_count > 0)
            return (NULL);

        // 死亡チェック
        if (check_death(philo))
            return (NULL);

        thinking(philo);

        if (take_forks(philo))
            return (NULL);

        if (check_death(philo))
        {
            put_down_forks(philo);
            return (NULL);
        }

        eating(philo);
        put_down_forks(philo);

        if (check_death(philo))
            return (NULL);

        sleeping(philo);
    }
}
