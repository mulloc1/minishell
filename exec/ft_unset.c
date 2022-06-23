#include "minishell.h"
#include "hashtable.h"
#include <stdlib.h>

static int	ft_remove_env(t_cmd *cmd)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (cmd->argv[++i])
	{
		if (!ft_check_name_valid(cmd->argv[i], 0))
		{
			exit_status = 1;
			continue ;
		}
		hashtable_remove(cmd->table, cmd->argv[i]);
	}
	return (exit_status);
}

static void	ft_child_proc(t_cmd *cmd)
{
	int	exit_status;

	exit_status = ft_remove_env(cmd);
	exit(exit_status);
}

void	ft_unset(t_cmd *cmd)
{
	pid_t	pid;
	int		exit_status;

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
	exit_status = ft_remove_env(cmd);
	// [전역변수] = exit_status
}

