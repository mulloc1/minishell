# include <stdio.h>
# include "env.h"

void displayTree(t_tree_node *node) {
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
# define TEST15 "Hello World \"$HOME\""
# define TEST16 "Hello World $HOME \"$HOME\""
# define TEST17 "Hello World $HOME"
# define TEST18 "ls -l | echo \"$HOME\" | < $HOME \"$HOME\""
# define TEST19 "echo    '$HOME' '$HOME' "
# define TEST20 "echo    '$HOME' '$HOME'  $HOME"
# define TEST21 "echo \"$HOME $HOME $HOME $HOME       $HOME\""
# define TEST22 "echo '$HOME     $HOME    \"$HOME\" '" 

//int	main(int argc, char *argv[], char *envp[])
//{
//	argv++;
//
//	t_init_struct *init_struct1 = test(TEST1, argc, envp);
//	t_init_struct *init_struct2 = test(TEST2, argc, envp);
//	t_init_struct *init_struct3 = test(TEST3, argc, envp);
//	t_init_struct *init_struct4 = test(TEST4, argc, envp);
//	t_init_struct *init_struct5 = test(TEST5, argc, envp);
//	t_init_struct *init_struct6 = test(TEST6, argc, envp);
//	t_init_struct *init_struct7 = test(TEST7, argc, envp);
//	t_init_struct *init_struct8 = test(TEST8, argc, envp);
//	t_init_struct *init_struct9 = test(TEST9, argc, envp);
//	t_init_struct *init_struct10 = test(TEST10, argc, envp);
//	t_init_struct *init_struct11 = test(TEST11, argc, envp);
//	t_init_struct *init_struct12 = test(TEST12, argc, envp);
//	t_init_struct *init_struct13 = test(TEST13, argc, envp);
//	t_init_struct *init_struct14 = test(TEST14, argc, envp);
//	t_init_struct *init_struct15 = test(TEST15, argc, envp);
//	t_init_struct *init_struct16 = test(TEST16, argc, envp);
//	t_init_struct *init_struct17 = test(TEST17, argc, envp);
//	t_init_struct *init_struct18 = test(TEST18, argc, envp);
//	system("leaks a.out");
//	return (0);
//}
