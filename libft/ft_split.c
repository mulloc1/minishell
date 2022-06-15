/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:05:38 by jaewchoi          #+#    #+#             */
/*   Updated: 2021/12/01 17:24:37 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static void	ft_free_arr(char **result, size_t r_index)
{
	size_t	i;

	i = 0;
	while (i <= r_index)
	{
		free(result[i]);
		result[i] = 0;
		i++;
	}
	free(result);
	result = 0;
}

static void	ft_fill_arr(char **result, char *str, char c, size_t size)
{
	size_t	len;
	size_t	start;
	size_t	r_index;

	start = 0;
	while (str[start] && str[start] == c)
		start++;
	r_index = 0;
	while (str[start] && r_index < size)
	{
		len = start;
		while (str[len] && str[len] != c)
			len++;
		result[r_index] = ft_substr(str, start, len - start);
		if (!result[r_index])
		{
			ft_free_arr(result, r_index);
			return ;
		}
		r_index++;
		while (str[len] && str[len] == c)
			len++;
		start = len;
	}
	result[r_index] = 0;
}

static size_t	ft_count_size(char *s, char c)
{
	size_t	result;
	size_t	i;

	result = 0;
	i = 0;
	if (s[0] && s[0] != c)
	{
		result++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			result++;
		i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	size;

	if (!s)
		return (0);
	size = ft_count_size((char *)s, c);
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (0);
	else if (size == 0)
	{
		result[0] = 0;
		return (result);
	}
	ft_fill_arr(result, (char *)s, c, size);
	return (result);
}
