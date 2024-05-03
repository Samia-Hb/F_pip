CFLAGS = -Wall -Wextra -Werror
CC = cc #-fsanitize=address -g3
NAME = pipex
SRCS = main.c pipex.c pipex_utils.c check_arg.c parsing.c\
		libft/ft_strncmp.c libft/ft_split.c libft/ft_strtrim.c libft/ft_strdup.c libft/ft_strjoin.c \
		ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_putnbr_base.c \
		ft_printf/ft_putnbr_signed.c ft_printf/ft_putnbr_unsigned.c ft_printf/ft_putstr.c ft_printf/ft_putnbr_base_adr.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: clean all