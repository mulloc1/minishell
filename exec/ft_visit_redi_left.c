#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// static void	ft_clear_cmd(t_cmd *cmd)
// {
// 	int i;

// 	if (cmd->out_fd > STDOUT)
// 		close(cmd->out_fd);
// 	free(cmd->path);
// 	cmd->path = NULL;
// 	i = -1;
// 	while(cmd->argv[++i])
// 		free(cmd->argv[i]);
// 	free(cmd->argv);
// 	cmd->argv = NULL;
// }

int	ft_visit_redi_left(t_token token, t_cmd *cmd)
{
	char	*filename;
	char	**split_name;
	int		result;

	split_name = ft_split_argv(token.token, cmd->table);
	filename = split_name[0];
	if (cmd->in_fd != STDIN)
		close(cmd->in_fd);
	result = TRUE;
	cmd->in_fd = open(filename, O_RDONLY);
	if (cmd->in_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		cmd->path_state = IN_PUT_ERR;
		result = FALSE;
	}
	free(split_name);
	free(filename);
	return (result);
}
