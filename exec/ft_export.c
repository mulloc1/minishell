/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:11:51 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:37:51 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	ft_child_proc(t_cmd *cmd)
{
	ft_set_fd(cmd);
	if (!cmd->argv[1])
		ft_export_print(cmd);
	else
		ft_add_env(cmd);
	exit(0);
}

void	ft_export(t_cmd *cmd)
{
	pid_t	pid;
	int		exit_code;
	char	*exit_str;

	if (cmd->is_pipe || !cmd->argv[1])
	{	
		pid = fork();
		if (pid < 0)
			ft_error("fork fail\n");
		else if (pid == 0)
			ft_child_proc(cmd);
		cmd->last_pid = pid;
		return ;
	}
	exit_code = ft_add_env(cmd);
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		ft_error("malloc fail\n");
	hashtable_insert(cmd->table, "?", exit_str);
	free(exit_str);
	cmd->last_pid = -1;
}
