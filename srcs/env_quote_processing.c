/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:00:25 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/23 18:53:16 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"

int	export_check(char *token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (ft_isprint(token[i]) && token[i] != ' ')
			if (!ft_strncmp(&token[i], "export ", 7))
				return (1);
	}
	return (0);
}

int	quote_check(char *token)
{
	int	i;

	i = 0;
	while (token[++i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			if (token[i] == token[0])
			{
				if (token[i] == '\'')
					return (SINGLE_QUOTE);
				else if (token[i] == '\"')
					return (DOUBLE_QUOTE);
			}
		}
	}
	return (NOT_QUOTE);
}

void	env_quote_processing(t_init_struct	*init_struct)
{
	t_tree_node	*cmd;
	//t_tree_node	*redi;
	int			i;
	int			temp;

	cmd = init_struct->tree->root;
	while (cmd)
	{
		// << 을 찾아서 환경변수 처리해주는 로직 작성
//		redi = cmd->left;
//		while (redi)
//		{
//			if (redi->type != DREDI_L)
//				env_processing(redi, 0, init_strcut->table);
//			redi = redi->left;
//		}
		i = 0;
		// not_auote 처리
		while (cmd->data.token[i])
		{
			temp = quote_check(&cmd->data.token[i]);
			if (temp == SINGLE_QUOTE)
				i = single_quote_processing(cmd, i);
			else if (temp == DOUBLE_QUOTE)
				i = double_quote_processing(cmd, i, init_struct->table);
			else
				i++;
//			else if ()
//				// export
//			else
//				i = not_quote_processing(cmd, i, init_struct->table);
		}
		cmd = cmd->right;
	}
}
