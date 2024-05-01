CFLAGS = -Wall -Wextra -Werror
CC = gcc #-fsanitize=address -g3
NAME = pipex
SRCS = pipex.c ft_strncmp.c ft_strjoin.c ft_split.c ft_strdup.c ft_strlen.c ft_strtrim.c execute_commands.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: clean all