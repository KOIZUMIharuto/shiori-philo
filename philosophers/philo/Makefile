# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shiori <shiori@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/16 19:37:40 by shiori            #+#    #+#              #
#    Updated: 2025/02/17 04:36:30 by shiori           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -I./include
SRCS =  init.c main.c monitor.c philo_routine.c thread.c utils.c
OBJS = $(SRCS:.c=.o)
RM = rm -f 

# -fsanitize=thre

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all