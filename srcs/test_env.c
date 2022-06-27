# include <stdio.h>
# include "env.h"

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

# define TEST1 "\"$HOME\""
# define TEST2 "\"$HOME $HOME\""
# define TEST3 "\"$HOME\" \"$HOME\""
# define TEST4 "\"$HOME\" \"$HOME\" \"$HOME\""
# define TEST5 "\'$HOME\'"
# define TEST6 "\'$HOME $HOME\'"
# define TEST7 "\'$HOME\' \'$HOME\'"
# define TEST8 "\'$HOME $HOME\' \'$HOME $HOME\'"
# define TEST9 "\"$HOME\" \'$HOME\' \"$HOME\""
# define TEST10 "\" $HOME \" \' $HOME \' \" $HOME \""
# define TEST11 "\'Hello $HOME\'\"$HOME $HOME\" \'$HOME $HOME\' \"$HOME\""
# define TEST12 "\'Hello $HOME\' \"Hello $HOME $HOME\" \'$HOME $HOME\' \"$HOME\""
# define TEST13 "\"MY HOME DIRCTORY : $HOME\""
# define TEST14 "\"MY HOME DIRCTORY : $HAHAHA\""

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
	test(TEST11, argc, envp);
	test(TEST12, argc, envp);
	test(TEST13, argc, envp);
	//system("leaks a.out");
	return (0);
}
