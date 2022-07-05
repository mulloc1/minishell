/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:12:23 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:12:24 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_open_pipe(t_cmd *cmd, t_tree_node *node)
{
	if (!node)
	{
		cmd->pipe[P_READ] = -1;
		cmd->pipe[P_WRITE] = -1;
		return ;
	}
	pipe(cmd->pipe);
	if (!cmd->is_pipe)
		cmd->is_pipe = TRUE;
}
