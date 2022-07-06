/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:09:07 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/06 14:32:45 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "sort_env_list.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_get_name_value(char *str, char **name, char **value)
{
	char	**split;
	int		result;

	split = ft_export_split(str);
	result = TRUE;
	*name = split[0];
	*value = split[1];
	if (!ft_check_name_valid(*name, 1))
	{
		free(*name);
		free(*value);
		result = FALSE;
	}
	free(split);
	return (result);
}

static int	ft_check_key_exist(t_cmd *cmd, char *key)
{
	if (hashtable_search(cmd->table, key))
	{
		free(key);
		return (TRUE);
	}
	return (FALSE);
}

static void	ft_free_name_value(char **name, char **value)
{
	free(*name);
	free(*value);
	*name = NULL;
	*value = NULL;
}

int	ft_add_env(t_cmd *cmd)
{
	int		i;
	int		exit_status;
	char	*name;
	char	*value;

	i = 0;
	exit_status = 0;
	while (cmd->argv[++i])
	{
		if (!ft_get_name_value(cmd->argv[i], &name, &value))
			exit_status = 1;
		else
		{
			if (!value && ft_check_key_exist(cmd, name))
				continue ;
			if (value)
				ft_modify_envp(cmd, cmd->argv[i], name);
			hashtable_insert(cmd->table, name, value);
			sort_env_list_insert(&cmd->env_list, name);
			if (!ft_strncmp(name, "PATH", ft_strlen(name)))
				ft_modify_split_path(cmd);
			ft_free_name_value(&name, &value);
		}
	}
	return (exit_status);
}
