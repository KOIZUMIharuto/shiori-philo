#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

# define MAX_PHILOSOPHERS 200
# define SUCCESS 0
# define ERROR 1

// メッセージ定義
# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_philosopher t_philosopher;

typedef struct s_data {
    int num_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long start_time;
    int must_eat_count;
    bool someone_died;
    bool all_satisfied;
    pthread_mutex_t state_mutex;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_t monitor;
    t_philosopher *philosophers;
} t_data;

typedef struct s_philosopher
{
    int             id;
    int             eat_count;
    long            last_meal_time;
    pthread_t       thread;
    t_data          *data;
    pthread_mutex_t meal_time_mutex;  // 追加
    pthread_mutex_t eat_count_mutex;  // 追加
} t_philosopher;






long get_current_time();
void *philosopher_routine(void *argv);
void print_status(t_philosopher *philo, char *status);
void thinking(t_philosopher *philo);
int take_forks(t_philosopher *philo);
void eating(t_philosopher *philo);
void put_down_forks(t_philosopher *philo);
void sleeping(t_philosopher *philo);
int init_data(t_data *data, int argc, char **argv);
void error_exit(char *message);
void cleanup_resources(t_data *data);
int check_death(t_philosopher *philo);
void *monitor_routine(void *arg);
int check_ate_count(t_philosopher *philosophers);



#endif