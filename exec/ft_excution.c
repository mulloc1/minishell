#include "minishell.h"
#include <sys/wait.h>

void	ft_excution(t_init_struct *init_struct)
{
	t_cmd	cmd;
	int		status;

	cmd.path = NULL;
	cmd.argv = NULL;
	cmd.envp = init_struct->envp;
	cmd.in_fd = STDIN;
	cmd.out_fd = STDOUT;
	cmd.builtins = FALSE;
	cmd.is_pipe = FALSE;
	cmd.table = init_struct->table;
	cmd.env_list = init_struct->list;
	ft_search_tree(init_struct->tree->root, &cmd);
	while (wait(&status) > 0);
}