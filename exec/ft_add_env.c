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
			hashtable_insert(cmd->table, name, value);
			sort_env_list_insert(&cmd->env_list, name);
			free(name);
			free(value);
		}
	}
	return (exit_status);
}
