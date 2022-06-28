#include "minishell.h"
#include "hashtable.h"
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

void	ft_add_env(t_cmd *cmd)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (cmd->argv[++i])
	{
		if (ft_get_name_value(cmd->argv[i], &name, &value))
		{
			hashtable_insert(cmd->table, name, value);
			free(name);
			free(value);
		}
	}
}
