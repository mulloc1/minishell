#include "minishell.h"
#include "hashtable.h"
#include "sort_env_list.h"
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
		sort_env_list_remove(&cmd->env_list, cmd->argv[i]);
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
	exit_code = ft_remove_env(cmd);
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		ft_error("malloc fail\n");
	hashtable_insert(cmd->table, "?", exit_str);
	free(exit_str);
	cmd->last_pid = -1;
}

