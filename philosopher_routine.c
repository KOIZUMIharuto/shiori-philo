// philosopher_routine.c
#include "philo.h"



// 考える
void thinking(t_philosopher *philo)
{
    // usleep(philo->data->time_to_eat * 1000);
    print_status(philo, "is thinking");
}

// フォークを取る
// int take_forks(t_philosopher *philo)
// {
//     int left_fork = philo->id;
//     int right_fork = (philo->id + 1) % philo->data->num_philosophers;

//     if (philo->id == philo->data->num_philosophers - 1)
//     {
//         // 最後の哲学者は右→左の順に取得
//         pthread_mutex_lock(&philo->data->forks[right_fork]);
//         print_status(philo, "has taken a right fork");
//         pthread_mutex_lock(&philo->data->forks[left_fork]);
//         print_status(philo, "has taken a left fork");
//     }
//     else
//     {
//         // 他の哲学者は左→右の順に取得
//         pthread_mutex_lock(&philo->data->forks[left_fork]);
//         print_status(philo, "has taken a left fork");
//         pthread_mutex_lock(&philo->data->forks[right_fork]);
//         print_status(philo, "has taken a right fork");
//     }

//     return (0);
// }

int take_forks(t_philosopher *philo)
{
    int first_fork, second_fork;
    
    // 1人の哲学者の特別なケース
    if (philo->data->num_philosophers == 1)
    {
        pthread_mutex_lock(&philo->data->forks[0]);
        print_status(philo, "has taken a fork");
        
        // フォークを1秒間保持（time_to_dieを超えないように）
        usleep(philo->data->time_to_die * 1000);
        
        // デッドロックを防ぐためにフォークを解放
        pthread_mutex_unlock(&philo->data->forks[0]);
        
        // 死亡を示す
        return (1);
    }

    // より慎重なフォークの取得方法
    first_fork = philo->id;
    second_fork = (philo->id + 1) % philo->data->num_philosophers;

    // 哲学者の順番を入れ替えて、デッドロックのリスクを減らす
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks[first_fork]);
        print_status(philo, "has taken a left fork");
        
        // わずかな遅延を入れて、競合を減らす
        usleep(100);
        
        pthread_mutex_lock(&philo->data->forks[second_fork]);
        print_status(philo, "has taken a right fork");
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[second_fork]);
        print_status(philo, "has taken a right fork");
        
        usleep(100);
        
        pthread_mutex_lock(&philo->data->forks[first_fork]);
        print_status(philo, "has taken a left fork");
    }
    
    return (0);
}



// 食べる
void eating(t_philosopher *philo)
{
    print_status(philo, "is eating");
    
    pthread_mutex_lock(&philo->data->state_mutex);
    philo->last_meal_time = get_current_time();
    philo->eat_count++;

    // デバッグ出力
    printf("Philosopher %d eat count: %d\n", philo->id + 1, philo->eat_count);

    // 指定された回数食事したら満足フラグを立てる
    if (philo->data->must_eat_count > 0 && 
        philo->eat_count >= philo->data->must_eat_count)
    {
        philo->is_satisfied = true;
        printf("Philosopher %d is satisfied\n", philo->id + 1);
    }
    pthread_mutex_unlock(&philo->data->state_mutex);
    
    // 食事中に定期的に死亡チェック
    long start_eat_time = get_current_time();
    while (get_current_time() - start_eat_time < philo->data->time_to_eat)
    {
        usleep(100);  // 100マイクロ秒ごとにチェック
        
        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->someone_died)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            return;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);
        
        // 死亡の可能性をチェック
        if (check_death(philo))
            return;
    }
}

// フォークを置く
void put_down_forks(t_philosopher *philo)
{
    int left_fork = philo->id;
    int right_fork = (philo->id + 1) % philo->data->num_philosophers;

    // フォークを解放
    pthread_mutex_unlock(&philo->data->forks[left_fork]);
    pthread_mutex_unlock(&philo->data->forks[right_fork]);
}


// 寝る
void sleeping(t_philosopher *philo)
{
    print_status(philo, "is sleeping");
    // 指定された時間だけ寝る
    usleep(philo->data->time_to_sleep * 1000);
}

