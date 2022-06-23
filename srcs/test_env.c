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
# define TEST11 "ls -l \"$HOME\""
# define TEST12 "ls -l \"\'$HOME\'\""
# define TEST13 "ls -l \"$HOME $HOME\""
# define TEST14 "ls -l \"$HOME\" \"$HOME\""
# define TEST15 "ls -l \"$HOME $HOME\" \"$HOME\""
# define TEST16 "ls -l \"$HOME$\""
# define TEST17 "ls -l \"$HOME%\""
# define TEST18 "ls -l \"$HOME@\""
# define TEST19 "ls -l \"$HOME$ \""
# define TEST20 "ls -l $HOME"
# define TEST21 "ls -l \'$HOME\' \"$HOME\""

int	main(int argc, char *argv[], char *envp[])
{
	argv++;
	test(TEST11, argc, envp);
	test(TEST12, argc, envp);
	test(TEST13, argc, envp);
	test(TEST14, argc, envp);
	test(TEST15, argc, envp);
	test(TEST16, argc, envp);
	test(TEST17, argc, envp);
	test(TEST18, argc, envp);
	test(TEST19, argc, envp);
	test(TEST20, argc, envp);
	test(TEST21, argc, envp);
	//system("leaks a.out");
	return (0);
}
