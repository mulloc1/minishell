/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:30:05 by jaewchoi          #+#    #+#             */
/*   Updated: 2021/11/26 13:26:20 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s2_len;

	if (*s2 == '\0')
		return ((char *)s1);
	s2_len = ft_strlen(s2);
	i = 0;
	while (s1[i] && s2_len <= n - i)
	{
		if (s1[i] == s2[0] && !ft_strncmp(&s1[i], s2, s2_len))
			return ((char *)&s1[i]);
		i++;
	}
	return (0);
}
