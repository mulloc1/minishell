#include "minishell.h"
#include "libft.h"
#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	ft_parsing_env(char *str, t_cmd *cmd)
{
	char	*key;
	char	*value;
	int		i;
	int		result;

	i = 0;
	while (str[++i])
		if (str[i] == ' ')
			break ;
	key = malloc(sizeof(char) * i);
	if (!key)
		ft_error("malloc fail\n");
	key[i - 1] = '\0';
	result = i;
	while (--i > 0)
		key[i - 1] = str[i];
	value = hashtable_search(cmd->table, key);
	free(key);
	ft_putstr_fd(value, cmd->pipe[P_WRITE]);
	return (result);
}

static void	*ft_print_line(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != ' '\
		&& str[i + 1] != '\'' && str[i + 1] != '\"')
			i += ft_parsing_env(str[i], cmd);
		else
			write(cmd->pipe[P_WRITE], &str[i++], 1);
	}
}

void	ft_parsing_multiline(char *eof, t_cmd *cmd)
{
	char	*str;
	size_t	len;

	while (1)
	{
		str = readline("> ");
		len = ft_strlen(str);
		if (!ft_strncmp(eof, str, len + 10))
			break ;
		ft_print_line(str, cmd);
		free(str);
	}
	free(str);
}
