#include "minishell.h"
#include "libft.h"
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options
static int	ft_is_builtin(t_cmd *cmd)
{
	const char	**builtins = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int	i;

	i = -1;
	while (builtins[++i])
	{
		if (!ft_strncmp(cmd->argv[0], builtins[i], 10))
		{
			cmd->builtins = i + 1;
			return (TRUE);
		}
	}
	return (FALSE);
}

int	ft_visit_cmd(t_token token, t_cmd *cmd)
{
	cmd->argv = ft_split(token.token, ' ');
	if (!cmd->argv)
		ft_error("split malloc fail\n");
	if (ft_is_builtin(cmd))
		return (SUCCESS);
	cmd->path = ft_get_path(cmd->argv[0], cmd->envp);
	return (SUCCESS);
}
