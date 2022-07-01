#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	ft_pop_envp(char **envp, char *name)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], name, ft_strlen(name)))
			break ;
	}
	free(envp[i]);
	while (envp[++i])
	{
		envp[i - 1] = envp[i];
	}
	envp[i - 1] = NULL;
}

static void	ft_copy_envp(char **new, char **old)
{
	int	i;

	i = -1;
	while (old[++i])
	{
		new[i] = ft_strdup(old[i]);
		if (!new[i])
			ft_error("malloc fail\n");
		free(old[i]);
	}
	free(old);
}

void	ft_modify_envp(t_cmd *cmd, char *str, char *new_key)
{
	char	**new_envp;
	int		i;

	i = -1;
	while (cmd->envp[++i])
	{
		if (cmd->envp[i][ft_strlen(new_key)] == '=' &&\
		!ft_strncmp(cmd->envp[i], new_key, ft_strlen(new_key)))
		{
			free(cmd->envp[i]);
			cmd->envp[i] = ft_strdup(str);
			if (!cmd->envp[i])
				ft_error("malloc fail\n");
			return ;
		}
	}
	new_envp = ft_calloc(i + 1, sizeof(char *));
	if (!new_envp)
		ft_error("malloc fail\n");
	ft_copy_envp(new_envp, cmd->envp);
	cmd->envp = new_envp;
}
