#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/stat.h>

// 디렉토리 fail 126
// 파일 권한 없음 fail 126

static int	ft_permission_check(t_cmd *cmd, struct stat st)
{
	char			*id_str;
	unsigned int	id_digit;

	id_str = hashtable_search(cmd->table, "UID");
	if (id_str)
	{
		id_digit = ft_atoi(id_str);
		if (id_digit == st.st_uid && ((st.st_mode & S_IXUSR) == 0100))
			return (TRUE);
	}
	id_str = hashtable_search(cmd->table, "GROUPS");
	if (id_str)
	{
		id_digit = ft_atoi(id_str);
		if (id_digit == st.st_gid && ((st.st_mode & S_IXGRP) == 0100))
			return (TRUE);
	}
	if ((st.st_mode & S_IXOTH) == 0100)
		return (TRUE);
	return (FALSE);
}

static void	ft_check_path(t_cmd *cmd)
{
	struct stat		st;

	if (stat(cmd->argv[0], &st) < 0)
		return ;
	if (S_ISDIR(st.st_mode))
	{
		cmd->path_state = IS_DIR;
		return ;
	}
	else if (S_ISREG(st.st_mode))
	{
		if (!ft_permission_check(cmd, st));
		{
			cmd->path_state = PM_DENIED;
			return ;
		}
	}
	cmd->path = ft_strdup(cmd->argv[0]);
	if (!cmd->path)
		ft_error("malloc fail\n");
}

static int	ft_path_join_check(t_cmd *cmd, char *env_path)
{
	char	*join_path;

	join_path = ft_strjoin(env_path, cmd->argv[0]);
}

void	ft_get_path(t_cmd *cmd)
{
	extern t_list	*path_list;
	t_list			*temp;

	if (!path_list)
		ft_create_path_list(cmd);
	ft_check_path(cmd);
	temp = path_list;
	while (!cmd->path && temp)
	{
		if (ft_path_join_check(cmd, temp->content))
			return ;
		temp = temp->next;
	}
	cmd->path_state = NOT_VALID;
}
