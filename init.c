// init.c
#include "philo.h"


// • Your(s) program(s) should take the following arguments:



int init_data(t_data *data, int argc, char **argv)
{
    int i;

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

    // フォークの初期化（ifの外に出す）
    for (i = 0; i < data->num_philosophers; i++)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i]);
            return (1);
        }
    }

    data->someone_died = false;
    data->start_time = get_current_time();

    if (pthread_mutex_init(&data->print_mutex, NULL) != 0 ||
        pthread_mutex_init(&data->death_mutex, NULL) != 0 ||
        pthread_mutex_init(&data->meal_mutex, NULL) != 0 ||
        pthread_mutex_init(&data->state_mutex, NULL) != 0)
        return (1);

    return (0);
}


// // 初期化関連のエラーチェック付き関数
// int initialize_philosophers(t_data *data, t_philosopher *philosophers)
// {
//     int i;

//     i = 0;
//     while(i < data->num_philosophers)
//     {
//         philosophers[i].id = i;
//         philosophers[i].eat_count = 0;
//         philosophers[i].is_satisfied = false;
//         philosophers[i].last_meal_time = get_current_time();
//         philosophers[i].data = data;

//         if (pthread_create(&philosophers[i].thread, NULL,
//                           philosopher_routine, &philosophers[i]) != 0)
//         {
//             // エラー発生時は既に作成したスレッドを終了
//             while (--i >= 0)
//                 pthread_(philosophers[i].thread, NULL);
//             return (1);
//         }
//         i++;
//     }
//     return (0);
// }


