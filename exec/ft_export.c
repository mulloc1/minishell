#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

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
	ft_set_fd(cmd);
	if (!cmd->argv[1])
		ft_export_print(cmd);
	else
		ft_add_env(cmd);
	exit(0);
}

void	ft_export(t_cmd *cmd)
{
	pid_t		pid;
	extern int	exit_code;

	if (cmd->is_pipe || !cmd->argv[1])
	{	
		pid = fork();
		if (pid < 0)
			ft_error("fork fail\n");
		else if (pid == 0)
			ft_child_proc(cmd);
		cmd->last_pid = pid;
		return ;
	}
	exit_code = ft_add_env(cmd);
	cmd->last_pid = -1;
}
