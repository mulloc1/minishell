#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	ft_set_signal(void)*())
{
	struct termios	tms;

	tcgetattr(STDIN, &tms);
	tms.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN, TCSANOW, &tms);
	printf("parent : %lu\n", tms.c_lflag);
	signal(SIGINT, ft_sigint_handler);
	// signal(SIGQUIT, ft_sigquit_handler);
}

void	ft_set_child_signal(void)
{
	struct termios	tms;

	tcgetattr(STDIN, &tms);
	tms.c_lflag |= ECHOCTL;
	tcsetattr(STDIN, TCSANOW, &tms);
	printf("child : %lu\n", tms.c_lflag);
	signal(SIGINT, ft_child_sigint_handler);
	// signal(SIGQUIT, ft_child_sigquit_handler);
}

void	print_tms(void)
{
	struct termios	tms;

	tcgetattr(STDIN, &tms);
	printf("print_tms : %lu\n", tms.c_lflag);
}
