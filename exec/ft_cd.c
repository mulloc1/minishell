/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:09:25 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:18:16 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "hashtable.h"
#include <sys/stat.h>
#include <stdlib.h>

static int	ft_change_dir(t_cmd *cmd, char *path)
{
	char		*pwd;
	char		*oldpwd;
	char		*newpwd;

	if (path)
		pwd = path;
	else
		pwd = hashtable_search(cmd->table, "HOME");
	oldpwd = getcwd(NULL, 10);
	chdir(pwd);
	newpwd = getcwd(NULL, 10);
	hashtable_insert(cmd->table, "PWD", newpwd);
	hashtable_insert(cmd->table, "OLDPWD", oldpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}

static int	ft_cd_error(char *path, int flag)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (flag)
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": Not a directory", 2);
	return (1);
}

static int	ft_check_cd_path(t_cmd *cmd)
{
	struct stat	st;

	if (!cmd->argv[1])
		return (ft_change_dir(cmd, NULL));
	if (stat(cmd->argv[1], &st) < 0)
		return (ft_cd_error(cmd->argv[1], TRUE));
	else if (!S_ISDIR(st.st_mode))
		return (ft_cd_error(cmd->argv[1], FALSE));
	return (ft_change_dir(cmd, cmd->argv[1]));
}

static void	ft_child_proc(t_cmd *cmd)
{
	int	exit_status;

	exit_status = ft_check_cd_path(cmd);
	exit(exit_status);
}

void	ft_cd(t_cmd *cmd)
{
	pid_t	pid;
	int		exit_code;
	char	*exit_str;

	if (cmd->is_pipe)
	{	
		pid = fork();
		if (pid < 0)
			ft_error("fork fail\n");
		else if (pid == 0)
			ft_child_proc(cmd);
		cmd->last_pid = pid;
		return ;
	}
	exit_code = ft_check_cd_path(cmd);
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		ft_error("malloc fail\n");
	hashtable_insert(cmd->table, "?", exit_str);
	free(exit_str);
	cmd->last_pid = -1;
}
