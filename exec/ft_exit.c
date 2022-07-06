/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:31 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/06 23:49:56 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_run_exit(t_cmd *cmd)
{
	if (!cmd->argv[1])
		exit (0);
	else if (cmd->argv[2])
		ft_exit_error(NULL);
	ft_check_exit_status(cmd->argv[1]);
	return (1);
}

static void	ft_child_proc(t_cmd *cmd)
{
	int	exit_status;

	ft_set_fd(cmd);
	exit_status = ft_run_exit(cmd);
	exit(exit_status);
}

void	ft_exit(t_cmd *cmd)
{
	pid_t	pid;
	int		exit_code;
	char	*exit_str;

	if (cmd->is_pipe)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork fail\n");
		else if (pid == 0)
			ft_child_proc(cmd);
		cmd->last_pid = pid;
		return ;
	}
	printf("exit\n");
	exit_code = ft_run_exit(cmd);
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		ft_error("malloc fail\n");
	hashtable_insert(cmd->table, "?", exit_str);
	free(exit_str);
	cmd->last_pid = -1;
}
