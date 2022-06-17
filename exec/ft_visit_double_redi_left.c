#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	ft_multiline(char *eof, int out_fd)
{
	char	*str;
	size_t	len;

	while (1)
	{
		str = readline(">");
		len = ft_strlen(str);
		if (!ft_strncmp(eof, str, len + 10))
			break ;
		write(out_fd, str, len);
		write(out_fd, "\n", 1);
		free(str);
	}
	free(str);
	free(eof);
	close(out_fd);
}

static void	ft_read_multiline(char *eof, int out_fd)
{
	char	*new_eof;

	new_eof = ft_check_eof(eof);
	if (!new_eof)
		ft_pasing_multiline(eof, out_fd);
	else
		ft_multiline(new_eof, out_fd);	
}

int	ft_visit_double_redi_left(t_token token, t_cmd *cmd)
{
	if (cmd->in_fd != STDIN)
		close(cmd->in_fd);
	ft_open_pipe(cmd, (t_tree_node *)TRUE);
	cmd->in_fd = cmd->pipe[P_READ];
	ft_read_multiline(token.token, cmd->pipe[P_WRITE]);
	return (SUCCESS);
}
