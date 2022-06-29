#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

void	ft_create_path_list(t_cmd *cmd)
{
	extern t_list	*path_list;
	char			**path_split;
	t_list			*temp;
	int				i;

	path_split = ft_split(hashtable_search(cmd->table, "PATH"), ':');
	if (!path_split)
		ft_error("split malloc fail\n");
	path_list = ft_lstnew(path_split[0]);
	if (!path_list)
		ft_error("malloc fail\n");
	i = 0;
	while (path_split[++i])
	{
		temp = ft_listnew(path_split[i]);
		if (!temp)
			ft_error("malloc fail\n");
		ft_lstadd_front(&path_list, temp);
	}
	free(path_split[i]);
	free(path_split);
}

void	ft_delete_path_list(void *list)
{
	free(((t_list *)list)->content);
	free(list);
}
