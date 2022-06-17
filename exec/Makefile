SRC = *.c

OFLAG = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

LIBFT = ./libft.a

CFLAGS = -Wall -Wextra -Werror

all :
	gcc $(OFLAG) $(LIBFT) $(SRC) -o test

clean :
	rm -rf test test.dSYM

