/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:12:36 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:12:37 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_search_tree(t_tree_node *node, t_cmd	*cmd)
{
	if (!node)
		return ;
	if (!ft_visit(node->data, cmd))
		delorder(&(node->left));
	ft_search_tree(node->left, cmd);
	if (node->data.type == CMD)
	{
		ft_open_pipe(cmd, node->right);
		ft_cmd_run(cmd);
		if (node->right)
		{
			cmd->in_fd = cmd->pipe[P_READ];
			cmd->out_fd = STDOUT;
		}
	}
	ft_search_tree(node->right, cmd);
}
