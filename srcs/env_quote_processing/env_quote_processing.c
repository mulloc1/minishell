/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:00:25 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/26 14:32:29 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"

void	env_quote_processing(t_init_struct	*init_struct)
{
	t_tree_node	*node;
	int			i;
	int			temp;

	node = init_struct->tree->root;
	while (node)
	{
		i = 0;
		while (node->data.token[i])
		{
			temp = quote_check(&node->data.token[i]);
			if (temp == SINGLE_QUOTE)
				i += single_quote_processing(node, i);
			else if (temp == DOUBLE_QUOTE)
				i += double_quote_processing(node, i, init_struct->table);
			else if (temp == NOT_QUOTE)
				i++;//i += not_quote_processing(node, i, init_struct->table);
		}
		node = node->right;
	}
}
