/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:53:16 by jaewchoi          #+#    #+#             */
/*   Updated: 2021/11/25 13:07:23 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dst_index;
	size_t	src_index;
	size_t	dst_length;

	dst_length = ft_strlen(dst);
	if (dst_length >= n)
		return (ft_strlen(src) + n);
	dst_index = 0;
	src_index = 0;
	while (dst[dst_index])
		dst_index++;
	while (src_index < n - dst_length - 1 && src[src_index])
	{
		dst[dst_index] = src[src_index];
		dst_index++;
		src_index++;
	}
	dst[dst_index] = '\0';
	return (dst_length + ft_strlen(src));
}
