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

// 前方宣言
typedef struct s_data t_data;

typedef struct s_philosopher {
    pthread_t   thread;
    int         id;
    int         eating;
    int         eat_count;
    bool        is_satisfied;
    long        last_meal_time;
    t_data      *data;
} t_philosopher;

typedef struct s_data {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
    bool someone_died;
    bool all_satisfied;
    long start_time;
    pthread_mutex_t forks[MAX_PHILOSOPHERS];
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t state_mutex;
    pthread_t monitor;
    t_philosopher *philosophers;
} t_data;


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
int initialize_philosophers(t_data *data, t_philosopher *philosophers);
void cleanup_resources(t_data *data);
int check_death(t_philosopher *philo);
void *monitor_routine(void *arg);
int check_all_ate_must_eat_count(t_philosopher *philosophers);
void precise_sleep(long milliseconds);



#endif