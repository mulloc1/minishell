#include "minishell.h"

void	ft_split_env(char *str, char **name, char **value)
{
	int	i;
	int	j;

	i = -1;
	
}

void	ft_add_env(t_cmd *cmd)
{
	int		i;
	int		size;
	char	*name;
	char	*value;

	i = 0;
	while (cmd->argv[++i])
	{
		ft_split_env(cmd->argv[i], &name, &value);
	}
}
