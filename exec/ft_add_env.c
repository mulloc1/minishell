#include "minishell.h"
#include "libft.h"

static void	ft_export_error(char *name)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
}

static int	ft_check_name_valid(char *name)
{
	int i;

	if (!ft_isalpha(name[0]))
	{
		ft_export_error(name);
		return (FALSE);
	}
	i = 0;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]))
		{
			ft_export_error(name);
			return (FALSE);
		}
	}
	return (TRUE);
}

static char	*ft_remove_quote(char *str)
{
	int i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (str && str[++i])
	{
		if (str[i] == '\'' || str[i] == "\"")
		{
			cnt++;
			continue ;
		}
		if (!cnt)
			continue ;
		str[i - cnt] = str[i];
	}
	str[i - cnt] = str[i];
	return (str);
}

static int	ft_split_env(char *str, char **name, char **value)
{
	char	**split;
	int		result;

	split = ft_split(str, '=');
	if (!split)
		ft_error("split malloc fail\n");
	result = TRUE;
	*name = ft_remove_quote(split[0]);
	*value = ft_remove_quote(split[1]);
	if (!ft_check_name_valid(*name))
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
	int		size;
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
