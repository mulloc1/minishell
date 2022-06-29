#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	ft_get_path(t_cmd *cmd)
{
	extern t_list	*path_list;
	t_list			*temp;
	char			*path_tmp;

	if (!path_list)
		ft_create_path_list(cmd);
	ft_check_path(cmd, ft_strdup(cmd->argv[0]));
	temp = path_list;
	path_tmp = ft_strjoin("/", cmd->argv[0]);
	if (!path_tmp)
		ft_error("malloc fail\n");
	while (!cmd->path && temp)
	{
		ft_check_join_path(cmd, temp->content, path_tmp);
		if (cmd->path_state)
			break ;
		temp = temp->next;
	}
	free(path_tmp);
	if (!cmd->path)
		cmd->path_state = NOT_VALID;
}
