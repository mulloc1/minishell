/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:53:12 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/30 17:23:06 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	ft_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	exit(1);
}

void	null_guard(void *ptr)
{
	if (!ptr)
		exit(1);
}
