#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	ft_set_fd(t_cmd *cmd)
{
	if (cmd->in_fd != STDIN)
	{
		dup2(cmd->in_fd, STDIN);
		close(cmd->in_fd);
	}
	if (cmd->out_fd != STDOUT)
	{
		dup2(cmd->out_fd, STDOUT);
		close(cmd->out_fd);
	}
	else if (cmd->pipe[P_WRITE] > 0)
		dup2(cmd->pipe[P_WRITE], STDOUT);
	close(cmd->pipe[P_READ]);
	close(cmd->pipe[P_WRITE]);
}

void	ft_export_error(char *name, int type)
{
	char	*cmd;

	if (type)
		cmd = "export: `";
	else
		cmd = "unset: `";
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
}

int	ft_check_name_valid(char *name, int type)
{
	int i;

	if (!ft_isalpha(name[0]))
	{
		ft_export_error(name, type);
		return (FALSE);
	}
	i = 0;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			ft_export_error(name, type);
			return (FALSE);
		}
	}
	return (TRUE);
}

void	ft_export_print(t_cmd *cmd)
{
	char	*name;
	char	*value;
	t_list	*temp;

	ft_set_fd(cmd);
	temp = cmd->env_list;
	while (temp)
	{
		name = temp->content;
		value = hashtable_search(cmd->table, name);
		printf("declare -x %s", name);
		if (value)
			printf("=\"%s\"\n", value);
		else
			printf("\n");
		temp = temp->next;
	}
	exit(0);
}

static int	ft_keydup(char **ret, char *src)
{
	int i;
	int result;

	i = -1;
	while (src[++i])
		if (src[i] == '=')
			break ;
	ret[0] = malloc(sizeof(char) * (i + 1));
	if (!ret[0])
		ft_error("malloc fail\n");
	ret[0][i] = '\0';
	result = i;
	while (i-- > 0)
		ret[0][i] = src[i];
	return (result);
}

char	**ft_export_split(char *src)
{
	int		i;
	char	**result;

	if (!src)
		return (NULL);
	result = malloc(sizeof(char *) * 3);
	if (!result)
		ft_error("malloc fail\n");
	result[2] = NULL;
	i = ft_keydup(result, src);
	if (!src[i])
		result[1] = NULL;
	else
	{
		result[1] = ft_strdup(&src[i + 1]);
		if (!result[1])
			ft_error("malloc fail\n");
	}
	return (result);
}
