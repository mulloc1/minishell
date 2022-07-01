#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <sys/stat.h>

void	ft_create_split_path(t_cmd *cmd)
{
	cmd->split_path = ft_split(hashtable_search(cmd->table, "PATH"), ':');
	if (!cmd->split_path)
		ft_error("malloc fail\n");
}

void	ft_modify_split_path(t_cmd *cmd)
{
	char	*new_path;
	int		i;

	i = -1;
	while (cmd->split_path[++i])
		free(cmd->split_path[i]);
	free(cmd->split_path);
	new_path = hashtable_search(cmd->table, "PATH");
	if (!new_path)
		cmd->split_path = ft_calloc(1, sizeof(char *));
	else
		cmd->split_path = ft_split(hashtable_search(cmd->table, "PATH"), ':');
	if (!cmd->split_path)
		ft_error("malloc fail\n");
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
