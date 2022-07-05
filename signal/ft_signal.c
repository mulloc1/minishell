/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:41:33 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:41:40 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	ft_set_signal(void (*sig_int)(int), void (*sig_quit)(int))
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}

void	ft_set_echoctl(int flag)
{
	struct termios	tms;

	tcgetattr(STDIN, &tms);
	if (flag)
		tms.c_lflag |= ECHOCTL;
	else
		tms.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN, TCSANOW, &tms);
}
