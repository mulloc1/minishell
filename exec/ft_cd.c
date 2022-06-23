#include "minishell.h"
#include "libft.h"
#include "hashtable.h"
#include <sys/stat.h>
#include <stdlib.h>

static void	ft_change_dir(t_cmd *cmd, char *path)
{
	char		*pwd;
	char		*oldpwd;

	if (path)
		pwd = path;
	else
		pwd = hashtable_search(cmd->table, "HOME");
	oldpwd = getcwd(NULL, 10);
	chdir(pwd);
	hashtable_insert(cmd->table, "PWD", pwd);
	hashtable_insert(cmd->table, "OLDPWD", oldpwd);
	free(oldpwd);
}

static void	ft_cd_error(char *path, int flag)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (flag)
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": Not a directory", 2);
}

void	ft_cd(t_cmd *cmd)
{
	struct stat st;

	if (!cmd->argv[1])
	{
		if (cmd->is_pipe)
			return ;
		ft_change_dir(cmd, NULL);
		return ;
	}
	if (stat(cmd->argv[1], &st) < 0)
	{
		ft_cd_error(cmd->argv[1], TRUE);
		return ;
	}
	else if (!S_ISDIR(st.st_mode))
	{
		ft_cd_error(cmd->argv[1], FALSE);
		return ;
	}
	if (!cmd->is_pipe)
		ft_change_dir(cmd, cmd->argv[1]);
}
