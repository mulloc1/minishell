/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_multiline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:12:27 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/07 13:29:41 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void	rl_replace_line(const char *text, int clear_undo);

static int	ft_parsing_env(char *str, t_cmd *cmd)
{
	char	*key;
	char	*value;
	int		i;
	int		result;

	i = 0;
	while (str[++i])
		if (ft_isspace(str[i]) || str[i] == '\n')
			break ;
	key = malloc(sizeof(char) * i);
	if (!key)
		ft_error("malloc fail\n");
	key[i - 1] = '\0';
	result = i;
	while (--i > 0)
		key[i - 1] = str[i];
	value = hashtable_search(cmd->table, key);
	free(key);
	ft_putstr_fd(value, cmd->pipe[P_WRITE]);
	return (result);
}

static void	ft_print_line(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != ' '\
		&& str[i + 1] != '\'' && str[i + 1] != '\"')
			i += ft_parsing_env(&str[i], cmd);
		else
			write(cmd->pipe[P_WRITE], &str[i++], 1);
	}
}

void	ft_read_parsing(char *eof, t_cmd *cmd)
{
	char	*str;
	size_t	len;

	while (1)
	{
		write(1, "> ", 2);
		str = ft_strdup("");
		if (!str)
			ft_error("malloc fail\n");
		str = ft_gnl(str);
		if (!str)
			break ;
		len = ft_strlen(eof);
		if (!ft_strncmp(eof, str, len) && str[len] == '\n')
			break ;
		ft_print_line(str, cmd);
		free(str);
	}
	free(str);
}
