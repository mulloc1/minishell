#include "minishell.h"
#include "libft.h"

// static char	*ft_remove_quote(char *str)
// {
// 	int i;
// 	int	cnt;

// 	i = -1;
// 	cnt = 0;
// 	while (str && str[++i])
// 	{
// 		if (str[i] == '\'' || str[i] == "\"")
// 		{
// 			cnt++;
// 			continue ;
// 		}
// 		if (!cnt)
// 			continue ;
// 		str[i - cnt] = str[i];
// 	}
// 	str[i - cnt] = str[i];
// 	return (str);
// }

static int	ft_split_env(char *str, char **name, char **value)
{
	char	**split;
	int		result;

	split = ft_split(str, '=');
	if (!split)
		ft_error("split malloc fail\n");
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
		if (ft_split_env(cmd->argv[i], &name, &value))
		{
			// hashtable insert
			// key = name, value = value
		}
	}
}
