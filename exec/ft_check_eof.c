#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_copy_eof(char *eof, char *new_eof, char quote)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (eof[++i])
	{
		if (eof[i] == '\'' || eof[i] == '\"')
		{
			if (!quote)
				quote = eof[i];
			else if (quote == eof[i])
				quote = '\0';
			else
				new_eof[j++] = eof[i];
			continue ;
		}
		new_eof[j++] = eof[i];
	}
	return (j - 1);
}

char	*ft_check_eof(char *eof)
{
	char	*new_eof;
	int		eof_len;
	int		new_eof_len;

	eof_len = ft_strlen(eof);
	new_eof = ft_calloc(eof_len, sizeof(char));
	if (!new_eof)
		ft_error("malloc fail\n");
	new_eof_len = ft_copy_eof(eof, new_eof, '\0');
	if (eof_len == new_eof_len)
	{
		free(new_eof);
		new_eof = NULL;
	}
	return (new_eof);
}
