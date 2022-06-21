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
			init_struct->tree = ft_parser(str);
			// tree에서 표준입력을 count해서 17개 이상이면 shell 종료시키기
			env_quote_processing(init_struct);
			delete_tree(init_struct->tree);
			init_struct->tree = NULL;
		}
		free(str);
	}
	return (0);
}
