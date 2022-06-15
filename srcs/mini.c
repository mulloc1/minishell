#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "hashtable.h"
#include "parser.h"
#include "libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_tree	*tree;

	argv++;
	init(argc, envp);
	while (1)
	{
		str = readline("minishell$ ");
		if (str && str[0] != '\0')
		{
			tree = ft_parser(str);
		 	add_history(str);
			delete_tree(tree);
		}
		free(str);
	}
	return (0);
}
