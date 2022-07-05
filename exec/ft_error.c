/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:12 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:10:13 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	ft_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	ft_set_echoctl(PRINT);
	exit(1);
}
