/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:10:04 by shiori            #+#    #+#             */
/*   Updated: 2025/02/17 03:29:50 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_current_time() {
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    ft_usleep(long milliseconds)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
}


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void cleanup_resources(char *str, t_program *program)
{
    int i;
    
    if (str)
    {
        write(2, str, ft_strlen(str));
        write(2, "\n", 1);
    }
    pthread_mutex_destroy(&program->print_mutex);
    pthread_mutex_destroy(&program->state_mutex);
    i = 0;
    while (i < program->num_of_philos)
    {
        pthread_mutex_destroy(&program->forks[i]);
        i++;
    }
    free(program->forks);
    free(program->philos);
}



int ft_atoi(const char *str)
{
    int i=0;
    int sign=1;
    int result=0;
  
    if(str[i]=='-' || str[i]=='+')
    {
        if(str[i]=='-')
            sign=-1;
        i++;
    }
    while(str[i]>='0' && str[i]<='9')
    {
        result=result*10+(str[i]-'0');
        i++;
    } 
    return (sign*result);
}
