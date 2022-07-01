#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

// exit 인자는 exit명령어의 종료상태
// 인자의 수는 0, 1
// bash: exit: too many arguments
// -> exit_status : 1
// 인자의 범위는 LONG_MIN ~ LONG_MAX
// bash: exit: -9223372036854775809: numeric argument required
// bash: exit: 9223372036854775808: numeric argument required
// -> exit_status : 255
// +, - 부호는 한 개는 허용한다.

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

static int	ft_run_exit(t_cmd *cmd)
{
	if (!cmd->argv[1])
		exit (0);
	else if (cmd->argv[2])
		return (ft_exit_error(NULL));
	ft_check_exit_status(cmd->argv[1]);
	return (1);
}

static void	ft_child_proc(t_cmd *cmd)
{
	int	exit_status;

	ft_set_fd(cmd);
	exit_status = ft_run_exit(cmd);
	exit(exit_status);
}

void	ft_exit(t_cmd *cmd)
{
	pid_t	pid;
	int		exit_code;
	char	*exit_str;

	if (cmd->is_pipe)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork fail\n");
		else if (pid == 0)
			ft_child_proc(cmd);
		cmd->last_pid = pid;
		return ;
	}
	printf("exit\n");
	exit_code = ft_run_exit(cmd);
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		ft_error("malloc fail\n");
	hashtable_insert(cmd->table, "?", exit_str);
	free(exit_str);
	cmd->last_pid = -1;
}
