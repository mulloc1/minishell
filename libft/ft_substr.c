/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:16:02 by jaewchoi          #+#    #+#             */
/*   Updated: 2021/11/23 18:19:49 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	size_t			i;
	unsigned int	temp;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	temp = start;
	while (i < len && s[temp])
	{
		temp++;
		i++;
	}
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, &s[start], i + 1);
	return (result);
}
