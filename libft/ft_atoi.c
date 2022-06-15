/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 21:03:52 by jaewchoi          #+#    #+#             */
/*   Updated: 2021/11/23 17:38:37 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static int	ft_check_over(size_t result, int minus)
{
	if (result >= LLONG_MAX && minus == 1)
		return (-1);
	else if (result > LLONG_MAX && minus == -1)
		return (0);
	return (result * minus);
}

static int	ft_str_to_int(char *str, int minus)
{
	size_t	result;

	result = 0;
	while (str && *str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return (ft_check_over(result, minus));
}

int	ft_atoi(const char *str)
{
	int		minus;
	char	*temp;

	temp = (char *)str;
	minus = 1;
	while (*temp == 32 || (*temp >= 9 && *temp <= 13))
		temp++;
	if (*temp == '+')
		temp++;
	else if (*temp == '-')
	{
		minus *= -1;
		temp++;
	}
	if (*temp >= '0' && *temp <= '9')
		return (ft_str_to_int(temp, minus));
	return (0);
}
