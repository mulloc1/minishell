#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#define	TEST1 "cat \" < file1 ls -l \" | cat "
#define	TEST2 "echo \" cat > file2 | ls -l \" | cat "
#define	TEST3 "echo \' \"echo HelloWorld\" \' | ls -l > file1 | wc -l"
#define	TEST4 "echo \"HelloWorld"
#define	TEST5 "echo HelloWorld\""

static int	ft_search_redirect(char *str)
{
	int	i;

	i = 0;
	while (!(str[i] == '>' || str[i] == '<') && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			ft_quote_shift(str, &i);
		i++;
	}
	if (!str[i])
		i = -1;
	return (i);
}

static int	ft_redirection_case(char *cmd, int *i)
{
	int	len;
	int	res;

	len = 0;
	res = 0;
	while (cmd[(*i) + len] == '<' || cmd[(*i) + len] == '>')
		len++;
	if (len > 2)
		return (-1);
	if (cmd[(*i)] == '<' && cmd[(*i) + 1] == '<')
		res = DREDI_L;
	else if (cmd[(*i)] == '<' || (cmd[(*i)] == '<' && cmd[(*i) + 1] == '>'))
		res = REDI_L;
	else if (cmd[(*i)] == '>' && cmd[(*i) + 1] == '>')
		res = DREDI_R;
	else if (cmd[(*i)] == '>')
		res = REDI_R;
	*i += len + 1;
	return (res);
}

static t_token	ft_redirection_token_make(char *cmd, int i)
{
	t_token	res;
	int		temp;
	int		len;

	temp = i;
	res.type = ft_redirection_case(cmd, &i);
		len = -1;
	while (cmd[++len + i] != ' ' && cmd[len + i])
		;
	res.token = ft_substr(cmd, i, len);
	ft_memset(cmd + temp, ' ', i - temp + len);
	return (res);
}

static void	ft_pipe_tree_parsing(char *cmd, t_tree_node *left, t_tree_node *right)
{
	int	temp;

	temp = ft_search_redirect(cmd);
	while (temp != -1)
	{
		left = insert_left_node(left, \
		(t_tree_node){ft_redirection_token_make(cmd, temp), 0, NULL, NULL});
		temp = ft_search_redirect(cmd);
	}
	right->data = (t_token){CMD, cmd};
}

t_tree	*ft_parser(char *str)
{
	t_tree_node	*temp;
	t_tree		*tree;
	char		**cmds;
	int			i;

	tree = create_bin_tree((t_tree_node){{0, 0}, 0, NULL, NULL});
	cmds = ft_split_mini(str, '|');
	temp = tree->root;
	ft_pipe_tree_parsing(cmds[0], tree->root, tree->root);
	i = 0;
	while (cmds[++i])
	{
		temp = insert_right_node(temp, (t_tree_node){{0, 0}, 0, NULL, NULL});
		ft_pipe_tree_parsing(cmds[i], temp, temp);
	}
	free(cmds[i]);
    free(cmds);
    return (tree);
}

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
//void	test(char	*str)
//{
//	t_tree	*tree;
//
//	printf("============== %s ==============\n", str);
//	tree = ft_parser(str);
//	displayTree(tree->root);
//}
//
//int	main(void)
//{
//	test(TEST1);
//	test(TEST2);
//	test(TEST3);
//	test(TEST4);
//	test(TEST5);
//	return (0);
//}
