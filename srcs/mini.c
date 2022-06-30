#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "hashtable.h"
#include "parser.h"
#include "libft.h"

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
		ft_error("bash: maximum here-document count exceeded\n");
}

int	is_spaces(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

void	syntax_error_check(t_init_struct *init_struct)
{
	t_tree_node	*cmd;
	t_tree_node *redi;

	cmd = init_struct->tree->root;
	while (cmd)
	{
		redi = cmd->left;
		while (redi)
		{
			if (redi->data.token == NULL || redi->data.token[0] == '\0')
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

int	main(int argc, char *argv[], char *envp[])
{
	t_init_struct	*init_struct;
	char			*str;

	argv++;
	init_struct = init(argc, envp);
	while (1)
	{
		str = readline("minishell$ ");
		if (str && str[0] != '\0')
		{
		 	add_history(str);
			if (str[0] != '|')
				init_struct->tree = ft_parser(str);
			if (init_struct->tree)
			{
				dredi_l_check(init_struct->tree->root);
				syntax_error_check(init_struct);
			}
			env_quote_processing(init_struct);
			//displayTree(init_struct->tree->root);
			ft_excution(init_struct);
			if (init_struct->tree)
			{
				delete_tree(init_struct->tree);
				init_struct->tree = NULL;
			}
		}
		free(str);
	}
	return (0);
}
