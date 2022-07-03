#include "minishell.h"
#include "hashtable.h"
#include "sort_env_list.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_get_name_value(char *str, char **name, char **value)
{
	char	**split;
	int		result;

	split = ft_export_split(str);
	result = TRUE;
	*name = split[0];
	*value = split[1];
	if (!ft_check_name_valid(*name, 1))
	{
		free(*name);
		free(*value);
		result = FALSE;
	}
	free(split);
	return (result);
}

static void	ft_check_key_exist(t_cmd *cmd, char *key, char **value)
{
	if (*value)
		return ;
	*value = hashtable_search(cmd->table, key);
	if (*value)
	{
		*value = ft_strdup(*value);
		if (!(*value))
			ft_error("malloc fail\n");
	}
}

int	ft_add_env(t_cmd *cmd)
{
	int		i;
	int		exit_status;
	char	*name;
	char	*value;

	i = 0;
	exit_status = 0;
	while (cmd->argv[++i])
	{
		if (!ft_get_name_value(cmd->argv[i], &name, &value))
			exit_status = 1;
		else
		{
			ft_check_key_exist(cmd, name, &value);
			if (value)
				ft_modify_envp(cmd, cmd->argv[i], name);
			hashtable_insert(cmd->table, name, value);
			sort_env_list_insert(&cmd->env_list, name);
			if (!ft_strncmp(name, "PATH", ft_strlen(name)))
				ft_modify_split_path(cmd);
			free(name);
			free(value);
		}
	}
	return (exit_status);
}
