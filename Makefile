# Makefile for Minishell

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -I./include
SRCS =  check_status.c error.c  init.c  main.c  monitor.c philosopher_routine.c philosophers.c time.c
OBJS = $(SRCS:.c=.o)
RM = rm -f 

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