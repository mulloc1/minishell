/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:00:25 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/01 13:37:42 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"
#include <stdlib.h>

char	*block_make_valid(char *block, t_hashtable *table)
{
	char	*temp;
	int		status;
	int		i;

	i = 0;
	temp = ft_strdup(block);
	while (temp[i])
	{
		status = quote_check(&temp[i]);
		if (status == SINGLE_QUOTE)
			i += single_quote_processing(&temp, i);
		else if (status == DOUBLE_QUOTE)
			i += double_quote_processing(&temp, i, table);
		if (status == NOT_QUOTE)
			i += not_quote_processing(&temp, i, table);
	}
	return (temp);
}

//static	void	processing(t_init_struct *init_struct, t_tree_node	*node)
//{
//	int	i;
//	int	temp;
//
//	i = 0;
//	while (node->data.token[i] && node->data.type != DREDI_L)
//	{
//		temp = quote_check(&node->data.token[i]);
//		if (temp == SINGLE_QUOTE)
//			i += single_quote_processing(node, i);
//		else if (temp == DOUBLE_QUOTE)
//			i += double_quote_processing(node, i, init_struct->table);
//		else if (temp == NOT_QUOTE)
//			i += not_quote_processing(node, i, init_struct->table);
//	}
//}
//
//void	env_quote_processing(t_init_struct	*init_struct)
//{
//	t_tree_node	*cmd;
//	t_tree_node	*redi;
//
//	cmd = init_struct->tree->root;
//	while (cmd)
//	{
//		redi = cmd->left;
//		while (redi)
//		{
//			processing(init_struct, redi);
//			redi = redi->left;
//		}
//		processing(init_struct, cmd);
//		cmd = cmd->right;
//	}
//}
