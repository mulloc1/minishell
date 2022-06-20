#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_tree	*create_bin_tree(t_tree_node root_node)
{
	t_tree		*bintree;
	t_tree_node	*node;

	bintree = malloc(sizeof(t_tree));
	if (bintree == NULL)
		ft_error("bintree malloc fail\n");
	node = malloc(sizeof(t_tree_node));
	if (node == NULL)
		ft_error("bintree malloc fail\n");
	*node = root_node;
	bintree->root = node;
	return (bintree);
}

t_tree_node	*insert_left_node(t_tree_node *parent, t_tree_node child)
{
	if (parent == NULL)
		return (NULL);
	if (parent->left == NULL)
	{
		parent->left = malloc(sizeof(t_tree_node));
		if (parent->left == NULL)
			ft_error("bintree malloc fail\n");
		*parent->left = child;
	}
	return (parent->left);
}

t_tree_node	*insert_right_node(t_tree_node *parent, t_tree_node child)
{
	if (parent == NULL)
		return (NULL);
	if (parent->right == NULL)
	{
		parent->right = malloc(sizeof(t_tree_node));
		if (parent->right == NULL)
			ft_error("bintree malloc fail\n");
		*parent->right = child;
	}
	return (parent->right);
}

void	delorder(t_tree_node **node)
{
	t_tree_node	*temp;

	if (*node)
	{
		delorder(&(*node)->left);
		delorder(&(*node)->right);
		temp = *node;
		*node = NULL;
		// free(temp->data.token);
		free(temp);
	}
}

void	delete_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	delorder(&tree->root);
	free(tree);
}
