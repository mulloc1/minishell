/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:16 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/06 14:29:21 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/wait.h>
#include <stdlib.h>

static void	ft_wait_child(t_cmd *cmd)
{
	char	*exit_str;
	int		status;
	int		exit_code;

	if (cmd->last_pid > 0)
	{
		waitpid(cmd->last_pid, &status, 0);
		if (ft_is_signal_end(status))
			exit_code = 128 + ft_get_signal_num(status);
		else
			exit_code = ft_exit_status(status);
		exit_str = ft_itoa(exit_code);
		if (!exit_str)
			ft_error("malloc fail\n");
		hashtable_insert(cmd->table, "?", exit_str);
		free(exit_str);
	}
	while (wait(NULL) > 0)
		;
}

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

	if (!init_struct->tree)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		hashtable_insert(init_struct->table, "?", "258");
		return ;
	}
	ft_init_struct_cmd(&cmd, init_struct);
	ft_set_echoctl(PRINT);
	ft_search_tree(init_struct->tree->root, &cmd);
	ft_set_signal(ft_sigint_handler_wait_child, ft_sigquit_handler_wait_child);
	init_struct->envp = cmd.envp;
	init_struct->split_path = cmd.split_path;
	init_struct->list = cmd.env_list;
	ft_wait_child(&cmd);
	ft_set_signal(ft_sigint_handler, ft_sigquit_handler);
	ft_set_echoctl(NOT_PRINT);
}
