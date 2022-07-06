/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visit_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:12:54 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/06 13:27:01 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	ft_is_builtin(t_cmd *cmd)
{
	const char	*builtins[8] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int			i;

	i = -1;
	while (builtins[++i])
	{
		if (!ft_strncmp(cmd->argv[0], builtins[i], 10))
		{
			cmd->builtins = i + 1;
			return (TRUE);
		}
	}
	return (FALSE);
}

int	ft_visit_cmd(t_token token, t_cmd *cmd)
{
	cmd->argv = ft_split_argv(token.token, cmd->table);
	if (!cmd->split_path)
		ft_create_split_path(cmd);
	if (ft_is_builtin(cmd))
		return (SUCCESS);
	ft_get_path(cmd);
	return (SUCCESS);
}
