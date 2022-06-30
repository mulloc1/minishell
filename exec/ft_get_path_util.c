#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <sys/stat.h>

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
		temp = ft_lstnew(path_split[i]);
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

void	ft_check_path(t_cmd *cmd, char *check_path)
{
	struct stat		st;

	if (!check_path)
		ft_error("malloc fail\n");
	if (stat(check_path, &st) < 0)
		free(check_path);
	else if (S_ISDIR(st.st_mode))
	{
		cmd->path_state = IS_DIR;
		free(check_path);
	}
	else if (S_ISREG(st.st_mode))
	{
		if ((st.st_mode & S_IXOTH) == S_IXOTH\
		&& (st.st_mode & S_IROTH) == S_IROTH)
			cmd->path = check_path;
		else
		{
			cmd->path_state = PM_DENIED;
			free(check_path);
		}
	}
}

void	ft_check_join_path(t_cmd *cmd, char *env_path, char *path_tmp)
{
	char	*join_path;

	join_path = ft_strjoin(env_path, path_tmp);
	ft_check_path(cmd, join_path);
}