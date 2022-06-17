#include "minishell.h"
#include "libft.h"
#include <sys/stat.h>
#include <stdlib.h>

void	ft_cd(t_cmd *cmd)
{
	struct stat st;

	if (!cmd->argv[1])
	{
		if (cmd->pipe[P_WRITE] > 0 || cmd->in_fd != STDIN)
			return ;
		chdir(getenv("HOME"));// hashtable 수정
		// hashtable pwd 수정
		return ;
	}
	if (stat(cmd->argv[1], &st) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return ;
	}
	else if (!S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": Not a directory", 2);
		return ;
	}
	if (cmd->pipe[P_WRITE] < 0 && cmd->in_fd == STDIN)
	{
		chdir(cmd->argv[1]);
		// hashtable pwd 수정
	}
}
