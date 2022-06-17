#include "minishell.h"

void	ft_builtin_run(t_cmd *cmd)
{
	if (cmd->builtins == ECHO)
		ft_echo(cmd);
	else if (cmd->builtins == CD)
		ft_cd(cmd);
	else if (cmd->builtins == PWD)
		ft_pwd(cmd);
	else if (cmd->builtins == EXPORT)
		ft_export(cmd);
	else if (cmd->builtins == UNSET)
		ft_unset(cmd);
	else if (cmd->builtins == ENV)
		ft_env(cmd);
	else
		ft_exit(cmd);
}
