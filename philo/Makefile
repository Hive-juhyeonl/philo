# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: JuHyeon <JuHyeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 00:00:00 by JuHyeon           #+#    #+#              #
#    Updated: 2025/09/07 23:17:00 by JuHyeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I./includes

SRCS    = srcs/main.c \
          srcs/utils.c \
          srcs/init.c \
          srcs/philo_routine.c \
          srcs/monitor.c \
          srcs/clean.c \
		  srcs/life.c

OBJS_DIR = objs/
OBJS    = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
