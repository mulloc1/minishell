#include "minishell.h"
#include <unistd.h>

void	ft_open_pipe(t_cmd *cmd, t_tree_node *node)
{
	if (!node)
	{
		cmd->pipe[P_READ] = -1;
		cmd->pipe[P_WRITE] = -1;
		return ;
	}
	pipe(cmd->pipe);
}
