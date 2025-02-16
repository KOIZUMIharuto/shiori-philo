// // philos/philo/init.c
// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   init.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/16 17:05:55 by shiori            #+#    #+#             */
// /*   Updated: 2025/02/16 18:21:49 by shiori           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->must_eat_count = ft_atoi(argv[5]);
	else
		philo->must_eat_count = -1;
}

void	init_philos(t_philo *philos, t_program *program, char **argv)
{
	int	i;

	i = 0;
    while (i < program->num_of_philos)
	{
        philos[i].id = i + 1;
		philos[i].eating = false;
		philos[i].eat_count = 0;
        init_input(&philos[i], argv);
        philos[i].last_meal_time = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].print_mutex = &program->print_mutex;
		philos[i].state_mutex = &program->state_mutex;
		philos[i].someone_died = &program->someone_died;
        philos[i].all_satisfied = &program->all_satisfied;
		philos[i].left_fork = &program->forks[i];
		if (i == 0)
			philos[i].right_fork = &program->forks[philos[i].num_of_philos - 1];
		else
			philos[i].right_fork = &program->forks[i - 1];
		i++;
	}
}


void init_forks(t_program *program)
{
    int i;
    pthread_mutex_t *forks;
    
    i = 0;
    forks = program->forks;
    while (i < program->num_of_philos)
    {
        pthread_mutex_init(&forks[i],NULL);
        i++;
    }
}
void   init_program(t_program *program)
{
    program->someone_died = false;
    program->all_satisfied = false;
    program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
    if (!program->philos)
        cleanup_resources("Error: malloc failed", program);
    if(pthread_mutex_init(&program->print_mutex, NULL))
        cleanup_resources("Error: Mutex failed", program);
    if(pthread_mutex_init(&program->state_mutex, NULL))
        cleanup_resources("Error:Mutex failed", program);
    program->forks = malloc(sizeof(pthread_mutex_t) * program->num_of_philos);
    if (!program->forks)
        cleanup_resources("Error: malloc failed", program);
    init_forks(program);
}







