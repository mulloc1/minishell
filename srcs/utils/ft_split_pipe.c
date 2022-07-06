/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:07:00 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/06 12:34:41 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_quote_shift(char const *s, int *idx)
{
	int	i;

	i = 0;
	while (s[++i + *idx])
	{
		if (s[*idx] == s[*idx + i])
		{
			*idx += i;
			break ;
		}
	}
}

static int	ft_word_cnt(char const *s, char c)
{
	int	i;
	int	flag;
	int	cnt;

	i = -1;
	flag = 0;
	cnt = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			ft_quote_shift(s, &i);
		if (s[i] != c && flag == 0)
		{
			cnt++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
	}
	return (cnt);
}

static char	*ft_word_create(char const *s, char *c, int *idx)
{
	char	*result;	
	int		len;
	int		i;

	len = -1;
	while (!ft_strchr(c, s[*idx + ++len]))
	{
		if (s[*idx + len] == '\"' || s[*idx + len] == '\'')
			ft_quote_shift(s + *idx, &len);
	}
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = s[i + *idx];
	*idx += len;
	return (result);
}

char	**ft_split_pipe(char const *s, char c)
{
	int		word_cnt;
	int		i;
	int		j;
	char	**result;
	char	sep[2];

	if (!s)
		return (NULL);
	word_cnt = ft_word_cnt(s, c);
	sep[0] = c;
	sep[1] = '\0';
	result = ft_calloc(word_cnt + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < word_cnt)
	{
		while (ft_strchr(sep, s[j]))
			j++;
		result[i] = ft_word_create(s, sep, &j);
	}
	return (result);
}
