/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:28:27 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/08 15:32:14 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "parser.h"
#include "libft.h"

void	dredi_l_check(t_tree_node *tree)
{
	t_tree_node	*redi;
	int			cnt;

	cnt = 0;
	while (tree)
	{
		redi = tree->left;
		while (redi)
		{
			if (redi->data.type == DREDI_L)
				cnt++;
			redi = redi->left;
		}
		tree = tree->right;
	}
	if (cnt > 16)
		ft_error("minishell: maximum here-document count exceeded\n");
}

int	is_spaces(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (0);
	return (1);
}

int	ft_isinvalid_token(t_tree_node *redi)
{
	if (!redi->data.token || ft_isspace(redi->data.token[0]) || redi->data.type == -1)
		return (1);
	return (0);
}

void	syntax_error_check(t_init_struct *init_struct)
{
	t_tree_node	*cmd;
	t_tree_node	*redi;

	cmd = init_struct->tree->root;
	while (cmd)
	{
		redi = cmd->left;
		while (redi)
		{
			if (ft_isinvalid_token(redi))
			{
				delete_tree(init_struct->tree);
				init_struct->tree = NULL;
				return ;
			}
			redi = redi->left;
		}
		if (is_spaces(cmd->data.token))
		{
			delete_tree(init_struct->tree);
			init_struct->tree = NULL;
			return ;
		}
		cmd = cmd->right;
	}
}
