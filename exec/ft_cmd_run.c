#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static void	ft_cmd_error(int path_state, char *path)
{
	int		exit_status;
	char	*msg;

	exit_status = 126;
	if (path_state == NOT_VALID)
	{
		msg = ": command not found";
		exit_status = 127;
	}
	else if (path_state == IS_DIR)
		msg = ": is a directory";
	else if (path_state == PM_DENIED)
		msg = ": Permission denied";
	else
		exit(1);
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(msg, 2);
	exit(exit_status);
}

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
	if (cmd->path_state)
		ft_cmd_error(cmd->path_state, cmd->argv[0]);
	ft_set_fd(cmd);
	execve(cmd->path, cmd->argv, cmd->envp);
	exit(1);
}

static void	ft_clear_cmd(t_cmd *cmd)
{
	int	i;

	close(cmd->pipe[P_WRITE]);
	if (cmd->in_fd > STDIN)
		close(cmd->in_fd);
	if (cmd->out_fd > STDOUT)
		close(cmd->out_fd);
	if (cmd->path)
		free(cmd->path);
	cmd->path = NULL;
	if (cmd->builtins)
		cmd->builtins = FALSE;
	if (!cmd->argv)
		return ;
	i = -1;
	while(cmd->argv[++i])
		free(cmd->argv[i]);
	free(cmd->argv);
	cmd->argv = NULL;
}

void	ft_cmd_run(t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->builtins)
	{
		ft_builtin_run(cmd);
		ft_clear_cmd(cmd);
		return ;
	}
	if (cmd->argv)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork fail\n");
		else if (pid == 0)
			ft_child_proc(cmd);
		cmd->last_pid = pid;
	}
	ft_clear_cmd(cmd);
}
