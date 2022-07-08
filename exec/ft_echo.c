/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:03 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/08 16:10:25 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_is_option(char *argv)
{
	int	i;

	if (argv[0] != '-')
		return (FALSE);
	i = 1;
	while (argv[i] && argv[i] == 'n')
		i++;
	if (argv[i])
		return (FALSE);
	return (TRUE);
}

static void	ft_print(char **argv)
{
	int	i;
	int	is_newline;
	int	flag;

	is_newline = ft_is_option(argv[1]);
	if (!is_newline)
	{
		printf("%s", argv[1]);
		if (argv[2])
			printf(" ");
	}
	i = 1;
	flag = is_newline;
	while (argv[++i])
	{
		if (flag && ft_is_option(argv[i]))
			continue ;
		flag = FALSE;
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
	}
	if (!is_newline)
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
