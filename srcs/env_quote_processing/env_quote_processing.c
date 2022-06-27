/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:00:25 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/27 19:40:40 by mulloc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"

static	void	processing(t_init_struct *init_struct, t_tree_node	*node)
{
	int	i;
	int	temp;

	i = 0;
	while (node->data.token[i])
	{
		temp = quote_check(&node->data.token[i]);
		if (temp == SINGLE_QUOTE)
			i += single_quote_processing(node, i);
		else if (temp == DOUBLE_QUOTE)
			i += double_quote_processing(node, i, init_struct->table);
		else if (temp == NOT_QUOTE)
			i += not_quote_processing(node, i, init_struct->table);
	}
}

void	env_quote_processing(t_init_struct	*init_struct)
{
	t_tree_node	*cmd;
	t_tree_node *redi;
	int			i;
	int			temp;

	cmd = init_struct->tree->root;
	while (cmd)
	{
		redi = cmd->left;
		while (redi)
		{
			processing(init_struct, redi);
			redi = redi->left;
		}
		processing(init_struct, cmd);
		cmd = cmd->right;
	}
}
