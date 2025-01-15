// check_status.c
#include "philo.h"

// 死亡監視用の関数
// int check_death(t_philosopher *philo)
// {
//     long current_time;
//     long time_since_last_meal;

//     // pthread_mutex_lock(&philo->data->state_mutex);
//     current_time = get_current_time();
//     time_since_last_meal = current_time - philo->last_meal_time;

//     if (time_since_last_meal > philo->data->time_to_die)
//     {
//         pthread_mutex_lock(&philo->data->print_mutex);
//         // if (!philo->data->someone_died)
//         // {
//             long death_time = current_time - philo->data->start_time;
//             printf("%ld %d died\n", death_time, philo->id + 1);
//             philo->data->someone_died = true;
//         // }
//         pthread_mutex_unlock(&philo->data->print_mutex);
//         // pthread_mutex_unlock(&philo->data->state_mutex);
//         return (1);
//     }
//     // pthread_mutex_unlock(&philo->data->state_mutex);
//     return (0);
// }

int check_death(t_philosopher *philo)
{
    long current_time;
    long time_since_last_meal;

    pthread_mutex_lock(&philo->data->state_mutex);
    current_time = get_current_time();
    time_since_last_meal = current_time - philo->last_meal_time;

    // より厳密な死亡判定
    if (time_since_last_meal > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        if (!philo->data->someone_died)
        {
            long death_time = current_time - philo->data->start_time;
            printf("%ld %d died\n", death_time, philo->id + 1);
            philo->data->someone_died = true;
        }
        pthread_mutex_unlock(&philo->data->print_mutex);
        pthread_mutex_unlock(&philo->data->state_mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->state_mutex);
    return (0);
}

// 全員が必要回数食べたかチェックする関数
int check_all_ate_must_eat_count(t_philosopher *philo)
{
    int i = 0;
    
    // must_eat_count が 0 より小さい場合は、チェックしない
    if (philo->data->must_eat_count < 0)
        return (0);

    pthread_mutex_lock(&philo->data->meal_mutex);
    
    // すべての哲学者が指定された回数以上食べているかを確認
    for (i = 0; i < philo->data->num_philosophers; i++)
    {
        // 一人でも指定回数食べていない哲学者がいれば、falseを返す
        if (philo->data->philosophers[i].eat_count < philo->data->must_eat_count)
        {
            pthread_mutex_unlock(&philo->data->meal_mutex);
            return (0);
        }
    }
    
    pthread_mutex_unlock(&philo->data->meal_mutex);

    // すべての哲学者が指定された回数食事した場合
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->someone_died)
    {
        printf("All philosophers have eaten %d times. Stopping simulation.\n", 
               philo->data->must_eat_count);
        philo->data->someone_died = true;  // 終了を確実にするためのフラグ
        philo->data->all_satisfied = true;  // 全員が満足したことを示すフラグ
    }
    pthread_mutex_unlock(&philo->data->print_mutex);

    return (1);
}




