/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:03 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:37:21 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	ft_print(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (!argv[i] || ft_strncmp(argv[1], "-n", 5))
		printf("\n");
}

static void	ft_child_proc(t_cmd *cmd)
{
	ft_set_fd(cmd);
	ft_print(cmd->argv);
	exit(0);
}

void	ft_echo(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork fail\n");
	else if (pid == 0)
		ft_child_proc(cmd);
	cmd->last_pid = pid;
}
