/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visit_double_redi_left.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:13:02 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/07 00:30:56 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*ft_gnl(void)
{
	char	buf[1024];
	int		buf_size;
	char	*temp;
	char	*result;

	result = ft_strdup("");
	if (!result)
		ft_error("malloc fail\n");
	buf[0] = '\0';
	while (!ft_strchr(buf, '\n'))
	{
		buf_size = read(0, buf, 1000);
		if (buf_size < 0)
			ft_error("read fail\n");
		else if (!result[0] && !buf_size)
		{
			free(result);
			return (NULL);
		}
		buf[buf_size] = 0;
		temp = result;
		result = ft_strjoin(result, buf);
		if (!result)
			ft_error("malloc fail\n");
		free(temp);
	}
	return (result);
}

static void	ft_read(char *eof, int out_fd)
{
	char	*str;
	size_t	len;

	while (1)
	{
		write(1, "> ", 2);
		str = ft_gnl();
		if (!str)
			break ;
		len = ft_strlen(eof);
		if (!ft_strncmp(eof, str, len) && str[len] == '\n')
			break ;
		write(out_fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
	free(eof);
}

static void	ft_read_multiline(char *eof, t_cmd *cmd)
{
	char	*new_eof;

	ft_set_echoctl(NOT_PRINT);
	ft_set_signal(ft_sigint_handler_here_doc, ft_sigquit_handler_here_doc);
	new_eof = ft_check_eof(eof);
	if (!new_eof)
		ft_read_parsing(eof, cmd);
	else
		ft_read(new_eof, cmd->pipe[P_WRITE]);
	close(cmd->pipe[P_WRITE]);
	exit(0);
}

int	ft_visit_double_redi_left(t_token token, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (cmd->in_fd != STDIN)
		close(cmd->in_fd);
	ft_open_pipe(cmd, (t_tree_node *)TRUE);
	cmd->in_fd = cmd->pipe[P_READ];
	pid = fork();
	if (pid < 0)
		ft_error("fork fail\n");
	else if (pid == 0)
		ft_read_multiline(token.token, cmd);
	close(cmd->pipe[P_WRITE]);
	waitpid(pid, &status, 0);
	ft_set_echoctl(PRINT);
	ft_set_signal(ft_sigint_handler_wait_child, ft_sigquit_handler_wait_child);
	if (ft_exit_status(status))
	{
		printf("\033[1A\033[11C\n");
		cmd->path_state = IN_PUT_ERR;
		return (FAIL);
	}
	return (SUCCESS);
}
