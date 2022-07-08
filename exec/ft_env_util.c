/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:05 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/08 16:45:36 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "sort_env_list.h"
#include <stdlib.h>

void	ft_pop_envp(char **envp, char *name)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(name);
	while (envp[++i])
	{
		if (envp[i][len] == '=' && !ft_strncmp(envp[i], name, ft_strlen(name)))
			break ;
	}
	if (envp[i])
	{
		free(envp[i]);
		while (envp[++i])
		{
			envp[i - 1] = envp[i];
		}
		envp[i - 1] = NULL;
	}
}

static void	ft_copy_envp(char **new, char **old, char *new_key_value)
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
	new[i] = ft_strdup(new_key_value);
	if (!new[i])
		ft_error("malloc fail\n");
	free(old);
}

void	ft_modify_envp(t_cmd *cmd, char *str, char *new_key)
{
	char	**new_envp;
	int		i;

	i = -1;
	while (cmd->envp[++i])
	{
		if (cmd->envp[i][ft_strlen(new_key)] == '=' && \
		!ft_strncmp(cmd->envp[i], new_key, ft_strlen(new_key)))
		{
			free(cmd->envp[i]);
			cmd->envp[i] = ft_strdup(str);
			if (!cmd->envp[i])
				ft_error("malloc fail\n");
			sort_env_list_remove(&cmd->env_list, new_key);
			return ;
		}
	}
	new_envp = ft_calloc(i + 2, sizeof(char *));
	if (!new_envp)
		ft_error("malloc fail\n");
	ft_copy_envp(new_envp, cmd->envp, str);
	cmd->envp = new_envp;
}
