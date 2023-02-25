
NAME = pipex

NAMEB = pipex_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c func1.c func2.c get_path.c

SRCSB = pipex_bonus.c func1.c func2.c get_path.c

INCLUDES = pipex.h

all: $(NAME) $(SRCSB)

$(NAME): $(INCLUDES) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

bonus: $(INCLUDES) $(SRCSB)
	$(CC) $(CFLAGS) $(SRCSB) -o $(NAME)

clean :
	rm -f $(NAME) $(BONUS) $(NAMEB)

fclean :	clean

re : fclean all

.PHONY: re all fclean clean bonus
