
#include "include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

#define	TEST1 "ls"
#define	TEST2 "ls > file1"
#define	TEST3 "ls >> file1"
#define	TEST4 "ls -al"
#define	TEST5 "ls -al > file1"
#define	TEST6 "cat < file1"
#define TEST7 "echo hello > file1 > file2"
#define TEST8 "cat > file2 < file1"
#define TEST9 "cat < file2 < file1"
#define TEST10 "echo hello >> file1 > file2"
#define TEST11 "echo hello >> file1 >> file2"
#define TEST12 "echo hello | cat"
#define TEST13 "echo hello > file1 | cat"
#define TEST14 "echo hello > file1 | cat < file1"
#define TEST15 "echo hello > file1 | echo hello"
#define TEST16 "echo hello > file1 | echo hello > file1"
#define TEST17 "echo hello | cat | cat | cat | cat | cat"
#define TEST18 "echo hello | cat | cat | ls | cat | cat"
#define TEST19 "echo hello | cat | null | ls | null | ls"
#define TEST20 "./a.out"
#define TEST21 "bash a.out"
#define TEST22 "cd"
#define TEST23 "cd /null"
#define TEST24 "cd /goinfre/jaewchoi/42seoul/7_Minishell/"
#define TEST25 "cd ../../42seoul/7_Minishell"
#define TEST26 "pwd"
#define TEST27 "env"
#define TEST28 "export"
#define TEST29 "export name=jaewchoi"
#define TEST30 "unset"
#define TEST31 "unset name"
#define TEST32 "exit"

#define TEST33 "echo \"asdfas n enfin\" | grep a < file1"
#define TEST34 "echo -n hello"
#define TEST35 "cd ../../../../../../../../../../../../../../../../"
#define TEST36 "ls ./srcs | grep .c > file1"
#define TEST37 "ls ./srcs | grep .c file2"

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

void	display(int i)
{
	printf("=================");
	switch (i)
	{
	case 1: 
		printf("%s", TEST1);
		break;
	case 2: 
		printf("%s", TEST2);
		break;
	case 3: 
		printf("%s", TEST3);
		break;
	case 4:
		printf("%s", TEST4);
		break;
	case 5:
		printf("%s", TEST5);
		break;
	case 6:
		printf("%s", TEST6);
		break;
	case 7:
		printf("%s", TEST7);
		break;
	case 8:
		printf("%s", TEST8);
		break;
	case 9:
		printf("%s", TEST9);
		break;
	case 10:
		printf("%s", TEST10);
		break;
	case 11:
		printf("%s", TEST11);
		break;
	case 12:
		printf("%s", TEST12);
		break;
	case 13:
		printf("%s", TEST13);
		break;
	case 14:
		printf("%s", TEST14);
		break;
	case 15:
		printf("%s", TEST15);
		break;
	case 16:
		printf("%s", TEST16);
		break;
	case 17:
		printf("%s", TEST17);
		break;
	case 18:
		printf("%s", TEST18);
		break;
	case 19:
		printf("%s", TEST19);
		break;
	case 20:
		printf("%s", TEST20);
		break;
	case 21:
		printf("%s", TEST21);
		break;
	case 22:
		printf("%s", TEST22);
		break;
	case 23:
		printf("%s", TEST23);
		break;
	case 24:
		printf("%s", TEST24);
		break;
	case 25:
		printf("%s", TEST25);
		break;
	case 26:
		printf("%s", TEST26);
		break;
	case 27:
		printf("%s", TEST27);
		break;
	case 28:
		printf("%s", TEST28);
		break;
	case 29:
		printf("%s", TEST29);
		break;
	case 30:
		printf("%s", TEST30);
		break;
	case 31:
		printf("%s", TEST31);
		break;
	case 32:
		printf("%s", TEST32);
		break;
	case 33:
		printf("%s", TEST33);
		break;
	case 34:
		printf("%s", TEST34);
		break;
	case 35:
		printf("%s", TEST35);
		break;
	case 36:
		printf("%s", TEST36);
		break;
	case 37:
		printf("%s", TEST37);
		break;
	default:
		break;
	}
	printf("=================\n");
}

t_tree	*ft_test1()
{
	t_tree	*tree;

	display(1);
	tree = create_bin_tree((t_tree_node){{CMD, "ls"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test2()
{
	t_tree	*tree;

	display(2);
	tree = create_bin_tree((t_tree_node){{CMD, "ls"}, 0, NULL, NULL});
	insert_left_node(tree->root, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test3()
{
	t_tree	*tree;

	display(3);
	tree = create_bin_tree((t_tree_node){{CMD, "ls"}, 0, NULL, NULL});
	insert_left_node(tree->root, (t_tree_node){{DREDI_R, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test4()
{
	t_tree	*tree;

	display(4);
	tree = create_bin_tree((t_tree_node){{CMD, "ls -al"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test5()
{
	t_tree	*tree;

	display(5);
	tree = create_bin_tree((t_tree_node){{CMD, "ls -al"}, 0, NULL, NULL});
	insert_left_node(tree->root, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test6()
{
	t_tree	*tree;

	display(6);
	tree = create_bin_tree((t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	insert_left_node(tree->root, (t_tree_node){{REDI_L, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test7()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(7);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	temp = insert_left_node(tree->root, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{REDI_R, "file2"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test8()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(8);
	tree = create_bin_tree((t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_left_node(tree->root, (t_tree_node){{REDI_R, "file2"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{REDI_L, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test9()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(9);
	tree = create_bin_tree((t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_left_node(tree->root, (t_tree_node){{REDI_L, "file2"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{REDI_L, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test10()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(10);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	temp = insert_left_node(tree->root, (t_tree_node){{DREDI_R, "file1"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{REDI_R, "file2"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test11()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(11);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	temp = insert_left_node(tree->root, (t_tree_node){{DREDI_R, "file1"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{DREDI_R, "file2"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test12()
{
	t_tree	*tree;

	display(12);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	insert_right_node(tree->root, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test13()
{
	t_tree	*tree;

	display(13);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	insert_left_node(tree->root, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	insert_right_node(tree->root, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test14()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(14);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	insert_left_node(tree->root, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{REDI_L, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test15()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(15);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	insert_left_node(tree->root, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test16()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(16);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	insert_left_node(tree->root, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test17()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(17);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test18()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(18);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "ls"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test19()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(19);
	tree = create_bin_tree((t_tree_node){{CMD, "echo hello"}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "cat"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "null"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "ls"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "null"}, 0, NULL, NULL});
	temp = insert_right_node(temp, (t_tree_node){{CMD, "ls"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test20()
{
	t_tree	*tree;

	display(20);
	tree = create_bin_tree((t_tree_node){{CMD, "./a.out"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test21()
{
	t_tree	*tree;

	display(21);
	tree = create_bin_tree((t_tree_node){{CMD, "bash a.out"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test22()
{
	t_tree	*tree;

	display(22);
	tree = create_bin_tree((t_tree_node){{CMD, "cd"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test23()
{
	t_tree	*tree;

	display(23);
	tree = create_bin_tree((t_tree_node){{CMD, "cd /null"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test24()
{
	t_tree	*tree;

	display(24);
	tree = create_bin_tree((t_tree_node){{CMD, "cd /goinfre/jaewchoi/42seoul/7_Minishell/"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test25()
{
	t_tree	*tree;

	display(25);
	tree = create_bin_tree((t_tree_node){{CMD, "cd ../../42seoul/7_Minishell"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test26()
{
	t_tree	*tree;

	display(26);
	tree = create_bin_tree((t_tree_node){{CMD, "pwd"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test27()
{
	t_tree	*tree;

	display(27);
	tree = create_bin_tree((t_tree_node){{CMD, "env"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test28()
{
	t_tree	*tree;

	display(28);
	tree = create_bin_tree((t_tree_node){{CMD, "export"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test29()
{
	t_tree	*tree;

	display(29);
	tree = create_bin_tree((t_tree_node){{CMD, "export name=jaewchoi"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test30()
{
	t_tree	*tree;

	display(30);
	tree = create_bin_tree((t_tree_node){{CMD, "unset"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test31()
{
	t_tree	*tree;

	display(31);
	tree = create_bin_tree((t_tree_node){{CMD, "unset name"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test32()
{
	t_tree	*tree;

	display(32);
	tree = create_bin_tree((t_tree_node){{CMD, "exit"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test33()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(33);
	tree = create_bin_tree((t_tree_node){{CMD, "echo \"asdfas n enfin\""}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "grep a"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{REDI_L, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test34()
{
	t_tree	*tree;

	display(34);
	tree = create_bin_tree((t_tree_node){{CMD, "echo -n hello"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test35()
{
	t_tree	*tree;

	display(35);
	tree = create_bin_tree((t_tree_node){{CMD, "cd ../../../../../../../../../../../../../../../../"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test36()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(36);
	tree = create_bin_tree((t_tree_node){{CMD, "ls ./srcs"}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "grep .c"}, 0, NULL, NULL});
	insert_left_node(temp, (t_tree_node){{REDI_R, "file1"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

t_tree	*ft_test37()
{
	t_tree	*tree;
	t_tree_node	*temp;

	display(37);
	tree = create_bin_tree((t_tree_node){{CMD, "ls ./srcs"}, 0, NULL, NULL});
	temp = insert_right_node(tree->root, (t_tree_node){{CMD, "grep .c file2"}, 0, NULL, NULL});
	displayTree(tree->root);
	return (tree);
}

int main()
{
	t_tree	*tree;

	tree = ft_test1();
	delete_tree(tree);
	tree = ft_test2();
	delete_tree(tree);
	tree = ft_test3();
	delete_tree(tree);
	tree = ft_test4();
	delete_tree(tree);
	tree = ft_test5();
	delete_tree(tree);
	tree = ft_test6();
	delete_tree(tree);
	tree = ft_test7();
	delete_tree(tree);
	tree = ft_test8();
	delete_tree(tree);
	tree = ft_test9();
	delete_tree(tree);
	tree = ft_test10();
	delete_tree(tree);
	tree = ft_test11();
	delete_tree(tree);
	tree = ft_test12();
	delete_tree(tree);
	tree = ft_test13();
	delete_tree(tree);
	tree = ft_test14();
	delete_tree(tree);
	tree = ft_test15();
	delete_tree(tree);
	tree = ft_test16();
	delete_tree(tree);
	tree = ft_test17();
	delete_tree(tree);
	tree = ft_test18();
	delete_tree(tree);
	tree = ft_test19();
	delete_tree(tree);
	tree = ft_test20();
	delete_tree(tree);
	tree = ft_test21();
	delete_tree(tree);
	tree = ft_test22();
	delete_tree(tree);
	tree = ft_test23();
	delete_tree(tree);
	tree = ft_test24();
	delete_tree(tree);
	tree = ft_test25();
	delete_tree(tree);
	tree = ft_test26();
	delete_tree(tree);
	tree = ft_test27();
	delete_tree(tree);
	tree = ft_test28();
	delete_tree(tree);
	tree = ft_test29();
	delete_tree(tree);
	tree = ft_test30();
	delete_tree(tree);
	tree = ft_test31();
	delete_tree(tree);
	tree = ft_test32();
	delete_tree(tree);
	tree = ft_test33();
	delete_tree(tree);
	tree = ft_test34();
	delete_tree(tree);
	tree = ft_test35();
	delete_tree(tree);
	tree = ft_test36();
	delete_tree(tree);
	tree = ft_test37();
	delete_tree(tree);
	tree = NULL;
	// system("leaks a.out");
	return 0;
}
