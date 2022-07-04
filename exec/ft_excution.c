#include "minishell.h"
#include "libft.h"
#include <sys/wait.h>
#include <stdlib.h>

static void	ft_init_struct_cmd(t_cmd *cmd, t_init_struct *init_struct)
{
	cmd->path = NULL;
	cmd->argv = NULL;
	cmd->envp = init_struct->envp;
	cmd->in_fd = STDIN;
	cmd->out_fd = STDOUT;
	cmd->builtins = FALSE;
	cmd->is_pipe = FALSE;
	cmd->table = init_struct->table;
	cmd->env_list = init_struct->list;
	cmd->path_state = 0;
	cmd->split_path = init_struct->split_path;
}

void	ft_excution(t_init_struct *init_struct)
{
	t_cmd	cmd;
	int		status;
	int		exit_code;
	char	*exit_str;

	if (!init_struct->tree)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		hashtable_insert(init_struct->table, "?", "258");
		return ;
	}
	ft_init_struct_cmd(&cmd, init_struct);
	ft_search_tree(init_struct->tree->root, &cmd);
	print_tms();
	init_struct->envp = cmd.envp;
	init_struct->split_path = cmd.split_path;
	if (cmd.last_pid > 0)
	{
		waitpid(cmd.last_pid, &status, 0);
		exit_code = status;
		exit_str = ft_itoa(exit_code);
		if (!exit_str)
			ft_error("malloc fail\n");
		hashtable_insert(cmd.table, "?", exit_str);
		free(exit_str);
	}
	while (wait(NULL) > 0)
		;
}
