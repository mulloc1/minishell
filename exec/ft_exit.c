#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// exit 인자는 exit명령어의 종료상태
// 인자의 수는 0, 1
// bash: exit: too many arguments
// -> exit_status : 1
// 인자의 범위는 LONG_MIN ~ LONG_MAX
// bash: exit: -9223372036854775809: numeric argument required
// bash: exit: 9223372036854775808: numeric argument required
// -> exit_status : 255
// +, - 부호는 한 개는 허용한다.

static void	ft_run_exit(t_cmd *cmd)
{
	unsigned char	exit_status;

	if (!cmd->argv[1])
		exit(0);
	else if (cmd->argv[2])
		ft_exit_error(NULL);
	exit_status = ft_get_exit_status(cmd->argv[1]);
	exit(exit_status);
}

void	ft_exit(t_cmd *cmd)
{
	pid_t			pid;

	if (cmd->is_pipe)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork fail\n");
		else if (pid == 0)
			ft_run_exit(cmd);
		cmd->last_pid = pid;
		return ;
	}
	printf("exit\n");
	ft_run_exit(cmd);
}
