#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_one_block_size(char *token, char quote)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (!quote && token[i] == ' ')
			break ;
		if ((token[i] == '\"' || token[i] == '\'') && !quote)
			quote = token[i];
		else if ((token[i] == '\"' || token[i] == '\'') && quote == token[i])
			quote = 0;
	}
	return (i);
}

static char *ft_parsing_block(char **token, t_hashtable *table)
{
	int		i;
	int		size;
	char	*block;
	char	*parsing_block;

	size = ft_one_block_size(*token, 0);
	block = ft_calloc(size + 1, sizeof(char));
	if (!block)
		ft_error("malloc fail\n");
	i = 0;
	while (i < size)
	{
		block[i++] = **token;
		*token++;
	}
	// parsing_block = 머선함수(block, table);
	free(block);
	return (parsing_block);
}

static int	ft_get_block_cnt(char *token, char quote)
{
	int		i;
	int		cnt;

	i = -1;
	while (token[++i] == ' ')
		;
	if (!token[i])
		return (0);
	cnt = 1;
	while (token[i])
	{
		if (token[i] == '\"' || token[i] == '\'')
		{
			if (!quote)
				quote = token[i];
			else if (quote == token[i])
				quote = 0;
		}
		if (!quote && token[i] == ' ' && token[i + 1] && token[i + 1] != ' ')
			cnt++;
		i++;
	}
	return (cnt);
}

char	**ft_split_argv(char *token, t_hashtable *table)
{
	char	**argv;
	int		block_cnt;
	int		i;

	block_cnt = ft_get_block_cnt(token, 0);
	if (!block_cnt)
		return (NULL);
	argv = ft_calloc(block_cnt + 1, sizeof(char *));
	if (!argv)
		ft_error("malloc fail\n");
	i = -1;
	while (++i < block_cnt)
	{
		while (*token == ' ')
			token++;
		argv[i] = ft_parsing_block(&token, table);
	}
}
