/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visit_redi_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:13:17 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:13:18 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_visit_redi_left(t_token token, t_cmd *cmd)
{
	char	*filename;
	char	**split_name;
	int		result;

	split_name = ft_split_argv(token.token, cmd->table);
	filename = split_name[0];
	if (cmd->in_fd != STDIN)
		close(cmd->in_fd);
	result = TRUE;
	cmd->in_fd = open(filename, O_RDONLY);
	if (cmd->in_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		cmd->path_state = IN_PUT_ERR;
		result = FALSE;
	}
	free(split_name);
	free(filename);
	return (result);
}
