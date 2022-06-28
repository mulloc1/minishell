/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:17:12 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/28 13:52:44 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	ft_isnaming(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

char	*check_env(char *temp, int idx)
{
	char	*res;
	int		i;

	res = ft_calloc(50, sizeof(char));
	while (temp[idx] != '$' && temp[idx])
		idx++;
	if (temp[idx] != '$' || temp[idx + 1] == '\0' || temp[idx + 1] == ' ' || temp[idx + 1] == '\"')
	{
		free(res);
		return (NULL);
	}
	i = -1;
	while (ft_isnaming(temp[++idx]) && temp[idx])
		res[++i] = temp[idx];
	return (res);
}

int	export_check(char *token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (ft_isprint(token[i]) && token[i] != ' ')
			if (!ft_strncmp(&token[i], "export ", 7))
				return (1);
	}
	return (0);
}

int	quote_check(char *token)
{
	int	i;

	i = 0;
	while (token[++i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			if (token[i] == token[0])
			{
				if (token[i] == '\'')
					return (SINGLE_QUOTE);
				else if (token[i] == '\"')
					return (DOUBLE_QUOTE);
			}
		}
	}
	return (NOT_QUOTE);
}
