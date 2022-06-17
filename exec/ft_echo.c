#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		// 환경변수, 명령어 확인
	}
}

void	ft_echo(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->argv[1], "-n", 5))
		ft_print(&(cmd->argv[2]));
	else
	{
		ft_print(&(cmd->argv[1]));
		printf("\n");
	}
}
