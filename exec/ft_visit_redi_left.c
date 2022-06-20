#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

static void	ft_clear_cmd(t_cmd *cmd)
{
	int i;

	if (cmd->out_fd > STDOUT)
		close(cmd->out_fd);
	free(cmd->path);
	cmd->path = NULL;
	i = -1;
	while(cmd->argv[++i])
		free(cmd->argv[i]);
	free(cmd->argv);
	cmd->argv = NULL;
}

int	ft_visit_redi_left(t_token token, t_cmd *cmd)
{
	if (cmd->in_fd != STDIN)
		close(cmd->in_fd);
	cmd->in_fd = open(token.token, O_RDONLY);
	if (cmd->in_fd < 0)
	{
		if (cmd->out_fd > 1)
			close(cmd->out_fd);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(token.token, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ft_clear_cmd(cmd);
		return (FAIL);
	}
	return (SUCCESS);
}
