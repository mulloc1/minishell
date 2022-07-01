#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	ft_get_path(t_cmd *cmd)
{
	int		i;
	char	*path_tmp;

	if (!cmd->split_path)
		ft_create_split_path(cmd);
	ft_check_path(cmd, ft_strdup(cmd->argv[0]));
	path_tmp = ft_strjoin("/", cmd->argv[0]);
	if (!path_tmp)
		ft_error("malloc fail\n");
	i = -1;
	while (!cmd->path && temp[++i])
	{
		ft_check_join_path(cmd, temp, path_tmp);
		if (cmd->path_state)
			break ;
	}
	free(path_tmp);
	if (!cmd->path && !cmd->path_state)
		cmd->path_state = NOT_VALID;
}
