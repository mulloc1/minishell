#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static void	ft_set_fd(t_cmd *cmd)
{
	if (cmd->in_fd != STDIN)
	{
		dup2(cmd->in_fd, STDIN);
		close(cmd->in_fd);
	}
	if (cmd->out_fd != STDOUT)
	{
		dup2(cmd->out_fd, STDOUT);
		close(cmd->out_fd);
	}
	else if (cmd->pipe[P_WRITE] > 0)
		dup2(cmd->pipe[P_WRITE], STDOUT);
	close(cmd->pipe[P_READ]);
	close(cmd->pipe[P_WRITE]);
}

static void	ft_child_proc(t_cmd *cmd)
{
	// if (cmd->path) -> cmd |
	ft_set_fd(cmd);
	if (!cmd->argv[1])
		printf("\n");
	else if (!ft_strncmp(cmd->argv[1], "-n", 5))
		printf("%s", cmd->argv[2]);
	else
		printf("%s\n", cmd->argv[1]);
	exit(1);
}

void	ft_echo(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork fail\n");
	else if (pid == 0)
		ft_child_proc(cmd);
	cmd->last_pid = pid;
}
