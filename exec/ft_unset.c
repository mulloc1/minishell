#include "minishell.h"

void	ft_unset(t_cmd *cmd)
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
		// hashtable delete
	}
}

