#include "minishell.h"
#include <stdio.h>
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

void	test(char *str)
{
	t_tree *tree = ft_parser(str);
	displayTree(tree->root);
	delete_tree(tree);
}

#define TEST1 "echo      <<      $PATH"

int main(void)
{
	test(TEST1);
	return (0);
}
