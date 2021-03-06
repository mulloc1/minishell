/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:12:33 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:37:57 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	ft_child_proc(t_cmd *cmd)
{
	char	*pwd;

	ft_set_fd(cmd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(1);
	printf("%s\n", pwd);
	exit(0);
}

void	ft_pwd(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork fail\n");
	else if (pid == 0)
		ft_child_proc(cmd);
	cmd->last_pid = pid;
}
