#include "minishell.h"
#include "unistd.h"

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
	char	*name;
	char	*value;

	ft_set_fd(cmd);
	// 환경변수 get
	// name = key, value = value
	while (name)
	{
		if (!value)
			continue ;
		printf("%s=%s\n", name, value);
	}
	exit(0);
}

void	ft_env(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork fail\n");
	else if (pid == 0)
		ft_child_proc(cmd);
	cmd->last_pid = pid;
}
