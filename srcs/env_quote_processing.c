/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:00:25 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/23 16:27:35 by jaebae           ###   ########.fr       */
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
	t_tree_node	*node;
	int			i;
	int			temp;

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
			temp = quote_check(&node->data.token[i]);
			if (temp == SINGLE_QUOTE)
				i = single_quote_processing(node, i);
			else if (temp == DOUBLE_QUOTE)
				i = double_quote_processing(node, i, init_struct->table);
			else
				i++;
		}
		node = node->right;
	}
}

//# include <stdio.h>
//
//void displayTree(t_tree_node *node)
//{
//	if (node)
//	{
//		switch (node->data.type)
//		{
//		case CMD:
//			printf("type : %s\t", "CMD");
//			break;
//		case REDI_L:
//			printf("type : %s\t", "<");
//			break;
//		case REDI_R:
//			printf("type : %s\t", ">");
//			break;
//		case DREDI_R:
//			printf("type : %s\t", ">>");
//			break;
//		case DREDI_L:
//			printf("type : %s\t", "<<");
//			break;
//		default:
//			break;
//		}
//		printf("%s\n", node->data.token);
//		displayTree(node->left);
//		displayTree(node->right);
//	}
//}
//
//t_init_struct	*test(char *str, int argc, char *envp[])
//{
//	t_init_struct	*init_struct;
//
//	init_struct = init(argc, envp);
//	init_struct->tree = ft_parser(str);
//	displayTree(init_struct->tree->root);
//	env_quote_processing(init_struct);
//	displayTree(init_struct->tree->root);
//	delete_tree(init_struct->tree);
//	init_struct->tree = NULL;
//	printf("\n");
//	return (init_struct);
//}
//
//# define TEST1 "\'Hello\'"
//# define TEST2 "\'Hello"
//# define TEST3 "Hello\'"
//# define TEST4 "\'\"Hello\"\'"
//# define TEST5 "\'\"Hello\'"
//# define TEST6 "\'Hello\"\'"
//# define TEST7 "echo \'\"Hello\"\'"
//# define TEST8 "echo \'\"Hello\'\'Hello\'"
//# define TEST9 "ls -l | echo \'\"Hello\"\'"
//# define TEST10 "ls -l | echo \'\"Hello\'\'Hello\'"
//# define TEST11 "ls -l \"$HOME\""
//# define TEST12 "ls -l \"\'$HOME\'\""
//# define TEST13 "ls -l \"$HOME $HOME\""
//# define TEST14 "ls -l \"$HOME\" \"$HOME\""
//# define TEST15 "ls -l \"$HOME $HOME\" \"$HOME\""
//# define TEST16 "ls -l \"$HOME$\""
//# define TEST17 "ls -l \"$HOME%\""
//# define TEST18 "ls -l \"$HOME@\""
//# define TEST19 "ls -l \"$HOME$ \""
//# define TEST20 "ls -l \"$HOME\""
//
//int	main(int argc, char *argv[], char *envp[])
//{
//	argv++;
//	test(TEST11, argc, envp);
//	test(TEST12, argc, envp);
//	test(TEST13, argc, envp);
//	test(TEST14, argc, envp);
//	test(TEST15, argc, envp);
//	test(TEST16, argc, envp);
//	test(TEST17, argc, envp);
//	test(TEST18, argc, envp);
//	test(TEST19, argc, envp);
//	//system("leaks a.out");
//	return (0);
//}
