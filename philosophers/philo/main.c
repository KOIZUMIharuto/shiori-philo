/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiori <shiori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:06:04 by shiori            #+#    #+#             */
/*   Updated: 2025/02/17 03:44:30 by shiori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int validate_command_line_args(char **argv)
{
    if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 ||
        ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0 || ((argv[5] && ft_atoi(argv[5]) <= 0) && (ft_atoi(argv[5]) < 0)))
        return (1);
    return (0);
}

int main(int argc, char **argv)
{
    t_program program;
    
    if (argc != 5 && argc != 6)
		return (write(2, "Error: Wrong argument count\n", 28), 1);
    program.num_of_philos = ft_atoi(argv[1]);
    if (validate_command_line_args(argv) == 1)
		return (write(2, "Error: Invalid argument\n", 24), 1);
    init_program(&program);
	init_philos(program.philos, &program, argv);
    thread_create(&program);
    cleanup_resources(NULL, &program);
    return (0);
}
