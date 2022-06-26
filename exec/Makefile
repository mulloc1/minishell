SRC = *.c ./hashtable/*

OFLAG = -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -g

LIBFT = ./libft.a

CFLAGS = -Wall -Wextra -Werror

all :
	gcc $(OFLAG) -I ./ $(LIBFT) $(SRC) -o test

clean :
	rm -rf test test.dSYM

