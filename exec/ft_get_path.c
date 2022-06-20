#include "minishell.h"
#include "libft.h"

static void	ft_set_string(t_cmd *cmd, char *str)
{
	int	len;

	len = ft_strlen(str) + 1;
	cmd->path = malloc(sizeof(char) * 15);
	cmd->argv = malloc(sizeof(char *) * 3);
	if (!cmd->path || !cmd->argv)
		ft_error("malloc fail\n");
	cmd->argv[0] = malloc(sizeof(char) * 6);
	cmd->argv[1] = malloc(sizeof(char) * len);
	cmd->argv[2] = NULL;
	if (!cmd->argv[0] || !cmd->argv[1])
		ft_error("malloc fail\n");
	ft_strlcpy(cmd->path, "/usr/bin/which", 20);
	ft_strlcpy(cmd->argv[0], "which", 10);
	ft_strlcpy(cmd->argv[1], str, len);
}

static char	*ft_set_path(char *path)
{
	int	i;

	i = -1;
	while (path[++i])
	{
		if (path[i] == '\n')
			path[i] = '\0';
	}
	return (path);
}

static char	*ft_read_pipe(int fd)
{
	char	*path;
	char	*temp;
	char	buf[512];
	int		buf_size;

	path = ft_strdup("");
	if (!path)
		ft_error("malloc fail\n");
	buf_size = 1;
	while (buf_size > 0)
	{
		buf_size = read(fd, buf, 500);
		if (buf_size < 0)
			ft_error("read fail\n");
		else if (!buf_size)
			break ;
		buf[buf_size] = '\0';
		temp = path;
		path = ft_strjoin(temp, buf);
		if (!path)
			ft_error("malloc fail\n");
		free(temp);
	}
	return (ft_set_path(path));
}

char	*ft_get_path(char *str, char **envp)
{
	t_cmd	cmd;
	int		status;
	char	*path;

	ft_set_string(&cmd, str);
	pipe(cmd.pipe);
	cmd.in_fd = STDIN;
	cmd.out_fd = STDOUT;
	cmd.envp = envp;
	cmd.builtins = FALSE;
	ft_cmd_run(&cmd);
	waitpid(cmd.last_pid, &status, 0);
	path = ft_read_pipe(cmd.pipe[P_READ]);
	close(cmd.pipe[P_READ]);
	return (path);
}
