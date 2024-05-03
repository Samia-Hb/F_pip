CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = libft.a
AR = ar rcs
SRCS = ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_toupper.c ft_tolower.c ft_substr.c ft_strrchr.c ft_strnstr.c ft_itoa.c ft_calloc.c ft_bzero.c ft_atoi.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strjoin.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strchr.c ft_isprint.c ft_strchr.c ft_strtrim.c ft_strncmp.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_striteri.c ft_split.c

BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJC = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)

bonus : $(BONUS_OBJC)
	$(AR) $(NAME) $(BONUS_OBJC)

clean:
	rm -f $(OBJS) $(BONUS_OBJC)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all bonus clean fclean re