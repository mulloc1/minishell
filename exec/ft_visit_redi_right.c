#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_visit_redi_right(t_token token, t_cmd *cmd)
{
	char	*filename;

	// filename = fsldnfldf(token.token, cmd->table);
	if (cmd->out_fd > 1)
		close(cmd->out_fd);
	cmd->out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (SUCCESS);
}
