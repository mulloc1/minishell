/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:52:41 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/08 17:01:39 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "sort_env_list.h"
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

static t_hashtable	*hashtable_init(char *envp[])
{
	t_hashtable	*table;
	char		**sp_envp;
	int			idx;

	table = hashtable_create();
	idx = -1;
	while (envp[++idx])
	{
		sp_envp = ft_export_split(envp[idx]);
		if (!ft_strncmp(sp_envp[0], "SHLVL", 6))
			increase_str_int(&sp_envp[1]);
		hashtable_insert(table, sp_envp[0], sp_envp[1]);
		free(sp_envp[0]);
		free(sp_envp[1]);
		free(sp_envp);
	}
	return (table);
}

static char	**envp_init(char *envp[])
{
	char	**res;
	int		cnt;
	int		idx;

	cnt = -1;
	while (envp[++cnt])
		;
	res = malloc((cnt + 1) * sizeof(char *));
	if (!res)
		ft_error("envp_init() char * malloc failed");
	idx = -1;
	while (++idx < cnt)
	{
		res[idx] = ft_strdup(envp[idx]);
		if (!res[idx])
			ft_error("envp_init() ft_strdup() failed");
		if (!ft_strncmp(res[idx], "SHLVL=", 6))
			increase_shlvl(&res[idx]);
	}
	return (res);
}

static t_list	*sort_env_list_init(char *envp[])
{
	char	**envp_sp;
	t_list	*list;
	int		i;

	list = NULL;
	i = -1;
	while (envp[++i])
	{
		envp_sp = ft_export_split(envp[i]);
		sort_env_list_insert(&list, envp_sp[0]);
		free(envp_sp[0]);
		free(envp_sp[1]);
		free(envp_sp);
	}
	sort_env_list_remove(&list, "_");
	return (list);
}

t_init_struct	*init(int argc, char *envp[])
{
	t_init_struct	*init_struct;

	if (argc != 1)
		exit(1);
	init_struct = malloc(sizeof(t_init_struct));
	if (!init_struct)
		return (NULL);
	init_struct->list = sort_env_list_init(envp);
	init_struct->table = hashtable_init(envp);
	init_struct->envp = envp_init(envp);
	init_struct->tree = NULL;
	init_struct->split_path = NULL;
	return (init_struct);
}
