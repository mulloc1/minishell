#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void rl_replace_line (const char *text, int clear_undo);

void	ft_sigint_handler(int num)
{
	num++;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_child_sigint_handler(int num)
{
	num++;
	exit(130);
}
