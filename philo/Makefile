NAME						= philo

CC							= cc
CFALGS						= -O2 -Wall -Wextra -Werror -g -fsanitize=thread
RM							= rm -rf

SRC_FILES					= philo.c\
							utils.c\
							eat_sleep_think.c\
							init.c\

HEADER						= philo.h

OBJS						= $(patsubst %.c, %.o, $(SRC_FILES))

all:						$(NAME)

$(NAME):					$(OBJS)
								$(CC) $(CFALGS) $(OBJS) -o $@

%.o:						%.c $(HEADER)
								$(CC) $(CFLAGS) -c $< -o $@

clean:
								$(RM) $(OBJS)

fclean:						clean
								$(RM) $(NAME)

re:							fclean all

.PHONY:						all clean fclean re