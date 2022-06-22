/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:00:25 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/22 16:17:46 by jaebae           ###   ########.fr       */
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
				i = double_quote_processing(node, i, init_struct->hashtable);
			else
				i++;
		}
		node = node->right;
	}
}

# include <stdio.h>

void displayTree(t_tree_node *node)
{
	if (node)
	{
		switch (node->data.type)
		{
		case CMD:
			printf("type : %s\t", "CMD");
			break;
		case REDI_L:
			printf("type : %s\t", "<");
			break;
		case REDI_R:
			printf("type : %s\t", ">");
			break;
		case DREDI_R:
			printf("type : %s\t", ">>");
			break;
		case DREDI_L:
			printf("type : %s\t", "<<");
			break;
		default:
			break;
		}
		printf("%s\n", node->data.token);
		displayTree(node->left);
		displayTree(node->right);
	}
}

t_init_struct	*test(char *str, int argc, char *envp[])
{
	t_init_struct	*init_struct;

	init_struct = init(argc, envp);
	init_struct->tree = ft_parser(str);
	displayTree(init_struct->tree->root);
	env_quote_processing(init_struct);
	displayTree(init_struct->tree->root);
	delete_tree(init_struct->tree);
	init_struct->tree = NULL;
	printf("\n");
	return (init_struct);
}

# define TEST1 "\'Hello\'"
# define TEST2 "\'Hello"
# define TEST3 "Hello\'"
# define TEST4 "\'\"Hello\"\'"
# define TEST5 "\'\"Hello\'"
# define TEST6 "\'Hello\"\'"
# define TEST7 "echo \'\"Hello\"\'"
# define TEST8 "echo \'\"Hello\'\'Hello\'"
# define TEST9 "ls -l | echo \'\"Hello\"\'"
# define TEST10 "ls -l | echo \'\"Hello\'\'Hello\'"

int	main(int argc, char *argv[], char *envp[])
{
	argv++;
	test(TEST1, argc, envp);
	test(TEST2, argc, envp);
	test(TEST3, argc, envp);
	test(TEST4, argc, envp);
	test(TEST5, argc, envp);
	test(TEST6, argc, envp);
	test(TEST7, argc, envp);
	test(TEST8, argc, envp);
	test(TEST9, argc, envp);
	test(TEST10, argc, envp);
	//system("leaks a.out");
	return (0);
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
//#define TEST11 "\'\"Hello\"\'"
//#define TEST12 "\"\'Hello\'\""
//#define TEST13 "\'\"Hello\'"
//#define TEST14 "\"\'Hello\'"
//int	main(void)
//{
//	printf("%s : %d\n", TEST1, quote_check(TEST1));
//	printf("%s : %d\n", TEST2, quote_check(TEST2));
//	printf("%s : %d\n", TEST3, quote_check(TEST3));
//	printf("%s : %d\n", TEST4, quote_check(TEST4));
//	printf("%s : %d\n", TEST5, quote_check(TEST5));
//	printf("%s : %d\n", TEST6, quote_check(TEST6));
//	printf("%s : %d\n", TEST11, quote_check(TEST11));
//	printf("%s : %d\n", TEST12, quote_check(TEST12));
//	printf("%s : %d\n", TEST13, quote_check(TEST13));
//	printf("%s : %d\n", TEST14, quote_check(TEST14));
//
//	printf("%s : %d\n", TEST7, export_check(TEST7));
//	printf("%s : %d\n", TEST8, export_check(TEST8));
//	printf("%s : %d\n", TEST9, export_check(TEST9));
//	printf("%s : %d\n", TEST10, export_check(TEST10));
//	return (0);
//}
