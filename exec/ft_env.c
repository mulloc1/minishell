/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:08 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:37:28 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"
#include <stdio.h>
#include <stdlib.h>

static void	ft_child_proc(t_cmd *cmd)
{
	int	i;

	ft_set_fd(cmd);
	i = -1;
	while (cmd->envp[++i])
		printf("%s\n", cmd->envp[i]);
	exit(0);
}

void	ft_env(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork fail\n");
	else if (pid == 0)
		ft_child_proc(cmd);
	cmd->last_pid = pid;
}
