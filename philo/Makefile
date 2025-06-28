NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -Iinclude
RM		=	rm -rf
OBJDIR	=	objs
SRCS        = \
			srcs/main.c \
			srcs/init.c \
			srcs/utils.c \
			srcs/routine.c \
			srcs/monitor.c \
			srcs/ft_atoi.c

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

$(OBJDIR)/%.o: %.c include/philo.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
