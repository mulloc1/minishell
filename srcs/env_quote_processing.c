/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:00:25 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/21 15:44:34 by jaebae           ###   ########.fr       */
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

int	single_quote_processing(t_tree_node *node, char *token)
{
	node++;
	token++;
	return (0);
}

int	double_quote_processing(t_tree_node *node, char *token)
{
	node++;
	token++;
	return (0);
}

void	env_quote_processing(t_init_struct	*init_struct)
{
	t_tree_node	*node;
	int			i;

	node = init_struct->tree->root;
	while (node)
	{
		if (export_check(node->data.token))
		{
			node = node->right;
			continue ;
		}
		i = 0;
		while (node->data.token[i])
		{
			if (quote_check(&node->data.token[i]) == SINGLE_QUOTE)
				i += double_quote_processing(node, &node->data.token[i]);
			else if (quote_check(&node->data.token[i]) == DOUBLE_QUOTE)
				i += single_quote_processing(node, &node->data.token[i]);
			else
				i++;
		}
		node = node->right;
	}
}

//#include <stdio.h>
//#define TEST1 "\"$PATH\""
//#define TEST2 "\"$PATH"
//#define TEST3 "$PATH\""
//#define TEST4 "\'$PAHT\'"
//#define TEST5 "\'$PATH"
//#define TEST6 "$PATH\'"
//#define TEST7 "export $PATH"
//#define TEST8 " export $PATH"
//#define TEST9 "cat $PATH"
//#define TEST10 "cat export$PATH"
//
//int	main(void)
//{
//	printf("%s : %d\n", TEST1, quote_check(TEST1));
//	printf("%s : %d\n", TEST2, quote_check(TEST2));
//	printf("%s : %d\n", TEST3, quote_check(TEST3));
//	printf("%s : %d\n", TEST4, quote_check(TEST4));
//	printf("%s : %d\n", TEST5, quote_check(TEST5));
//	printf("%s : %d\n", TEST6, quote_check(TEST6));
//
//	printf("%s : %d\n", TEST7, export_check(TEST7));
//	printf("%s : %d\n", TEST8, export_check(TEST8));
//	printf("%s : %d\n", TEST9, export_check(TEST9));
//	printf("%s : %d\n", TEST10, export_check(TEST10));
//	return (0);
//}
