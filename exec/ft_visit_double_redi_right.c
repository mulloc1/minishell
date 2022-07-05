/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visit_double_redi_right.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:13:07 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:13:07 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_visit_double_redi_right(t_token token, t_cmd *cmd)
{
	char	**split_name;
	char	*filename;

	split_name = ft_split_argv(token.token, cmd->table);
	filename = split_name[0];
	if (cmd->out_fd > 1)
		close(cmd->out_fd);
	cmd->out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(split_name);
	free(filename);
	return (SUCCESS);
}
