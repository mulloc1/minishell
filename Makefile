NAME = minishell

CC = gcc
CFLAG = -Werror -Wall -Wextra -I include -g
OFLAG = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include 
SRCS = srcs/mini.c \
	   srcs/bintree.c \
	   srcs/parser.c \
	   srcs/init.c \
	   srcs/ft_split_mini.c \
	   srcs/hashtable/hashtable_utils.c \
	   srcs/hashtable/hashtable_create.c \
	   srcs/hashtable/hashtable_delete.c \
	   srcs/hashtable/hashtable_insert.c \
	   srcs/hashtable/hashtable_remove.c \
	   srcs/hashtable/hashtable_search.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OBJS)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

re : fclean all

$(NAME) : $(OBJS)
	@make -C libft
	$(CC) $(OFLAG) $(CFLAG)  -o $@ $^ libft/libft.a

.PHONY : re fclean clean all
