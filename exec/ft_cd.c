#include "minishell.h"
#include "libft.h"
#include <sys/stat.h>
#include <stdlib.h>

// cd명령은 pipe로 다른 명령과 이어졌을 때 이동은 하지 않음
// working directory 이동 후 PWD, OLDPWD 수정

void	ft_cd(t_cmd *cmd)
{
	struct stat st;

	// cd
	if (!cmd->argv[1])
	{
		if (cmd->pipe[P_WRITE] > 0 || cmd->in_fd != STDIN)
			return ;
		chdir(getenv("HOME"));// hashtable 수정
		// hashtable pwd 수정
		return ;
	}
	// cd의 인자로 들어온 path확인
	// 해당 경로가 유효하지 않음
	if (stat(cmd->argv[1], &st) < 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return ;
	}
	// 경로는 유효하지만, 디렉토리가 아님
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
		// hashtable pwd, oldpwd 수정
	}
}
