/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:10:26 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/08 14:43:46 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_print_exit_err_msg(char *msg, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
}

int	ft_exit_error(char *argv)
{
	if (argv)
	{
		ft_print_exit_err_msg(": numeric argument required", argv);
		exit (255);
	}
	ft_print_exit_err_msg("too many arguments", NULL);
	return (1);
}

void	ft_check_exit_status(char *num)
{
	unsigned long	result;
	unsigned long	long_max;
	int				i;
	int				minus;

	result = 0;
	minus = 0;
	i = -1;
	if (num[0] == '+' || num[0] == '-')
		i++;
	if (num[0] == '-')
		minus = 1;
	long_max = LONG_MAX;
	while (num[++i])
	{
		if (!ft_isdigit(num[i]))
			ft_exit_error(num);
		result = (result * 10) + (num[i] - '0');
		if ((!minus && result > long_max) || (minus && result > long_max + 1))
			ft_exit_error(num);
	}
	exit ((unsigned char)result);
}
