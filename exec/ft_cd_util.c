/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:53:31 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/08 15:41:25 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_envp_copy(t_cmd *cmd, int size)
{
	char	**new;
	int		i;

	new = ft_calloc(size + 2, sizeof(char *));
	if (!new)
		ft_error("malloc fail\n");
	i = -1;
	while (cmd->envp[++i])
		new[i] = cmd->envp[i];
	free(cmd->envp);
	cmd->envp = new;
	return (i);
}

static void	ft_set_envp(t_cmd *cmd, int loc, char *pwd)
{
	if (!pwd)
		ft_error("malloc fail\n");
	free(cmd->envp[loc]);
	cmd->envp[loc] = pwd;
}

static int	ft_find_envp(t_cmd *cmd, char *key)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(key);
	while (cmd->envp[++i])
	{
		if (cmd->envp[i][len] == '=' \
		&& !ft_strncmp(cmd->envp[i], key, ft_strlen(key)))
			break ;
	}
	if (!(cmd->envp[i]))
		return (ft_envp_copy(cmd, i));
	return (i);
}

void	ft_pwd_set(t_cmd *cmd, char *old, char *new)
{
	int		loc;

	loc = ft_find_envp(cmd, "OLDPWD");
	ft_set_envp(cmd, loc, ft_strjoin("OLDPWD=", old));
	loc = ft_find_envp(cmd, "PWD");
	ft_set_envp(cmd, loc, ft_strjoin("PWD=", new));
}
