/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:37:32 by jaewchoi          #+#    #+#             */
/*   Updated: 2021/11/25 13:38:29 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static char	*ft_ptoa(int n, int size)
{
	char	temp[11];

	temp[size] = '\0';
	while (n)
	{
		temp[size - 1] = '0' + n % 10;
		n /= 10;
		size--;
	}
	return (ft_strdup(temp));
}

static char	*ft_mtoa(int n, int	size)
{
	char	temp[12];

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	temp[0] = '-';
	temp[size + 1] = '\0';
	n *= -1;
	while (n)
	{
		temp[size] = '0' + n % 10;
		n /= 10;
		size--;
	}
	return (ft_strdup(temp));
}

char	*ft_itoa(int n)
{
	char	*result;
	int		temp;
	int		size;

	temp = n;
	size = 0;
	if (temp == 0)
		return (ft_strdup("0"));
	while (temp)
	{
		temp /= 10;
		size++;
	}
	if (n < 0)
		result = ft_mtoa(n, size);
	else
		result = ft_ptoa(n, size);
	return (result);
}
