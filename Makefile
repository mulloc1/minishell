NAME = minishell

CC = gcc
CFLAG = -Werror -Wall -Wextra -I include -g
OFLAG = -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
SRCS = srcs/mini.c \
	   srcs/bintree.c \
	   srcs/parser.c \
	   srcs/init.c \
	   srcs/hashtable/hashtable_utils.c \
	   srcs/hashtable/hashtable_create.c \
	   srcs/hashtable/hashtable_insert.c \
	   srcs/hashtable/hashtable_remove.c \
	   srcs/hashtable/hashtable_search.c \
	   srcs/utils/ft_error.c \
	   srcs/utils/ft_split_mini.c \
	   srcs/sort_env_list/sort_env_list_insert.c \
	   srcs/sort_env_list/sort_env_list_remove.c \
	   srcs/env_quote_processing/double_quote_processing.c \
	   srcs/env_quote_processing/env_quote_processing.c \
	   srcs/env_quote_processing/env_utils.c \
	   srcs/env_quote_processing/not_quote_processing.c \
	   srcs/env_quote_processing/single_quote_processing.c \

EXECS = exec/ft_add_env.c \
		exec/ft_builtin_run.c \
		exec/ft_cd.c \
		exec/ft_check_eof.c \
		exec/ft_cmd_run.c \
		exec/ft_echo.c \
		exec/ft_env.c \
		exec/ft_exit.c \
		exec/ft_exit_util.c \
		exec/ft_export.c \
		exec/ft_export_util.c \
		exec/ft_get_path.c \
		exec/ft_get_path_util.c \
		exec/ft_open_pipe.c \
		exec/ft_parsing_multiline.c \
		exec/ft_pwd.c \
		exec/ft_search_tree.c \
		exec/ft_unset.c \
		exec/ft_visit.c \
		exec/ft_visit_cmd.c \
		exec/ft_visit_double_redi_left.c \
		exec/ft_visit_double_redi_right.c \
		exec/ft_visit_redi_left.c \
		exec/ft_visit_redi_right.c \
		exec/ft_excution.c

OBJS = $(SRCS:.c=.o)
OBJS += $(EXECS:.c=.o)

all : $(NAME)

clean :
	@make -C libft clean
	rm -f $(OBJS)

fclean : clean
	@make -C libft clean
	@rm -rf libft/libft.a
	rm -f $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

re : fclean all

$(NAME) : $(OBJS)
	@make -C libft
	$(CC) $(OFLAG) $(CFLAG) -o $@ $^ libft/libft.a

.PHONY : re fclean clean all
