/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:41:15 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/06 21:41:42 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

void	rl_replace_line(const char *text, int clear_undo);

void	ft_sigint_handler(int num)
{
	num++;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint_handler_wait_child(int num)
{
	num++;
	printf("\n");
}

void	ft_sigquit_handler(int num)
{
	num++;
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit_handler_wait_child(int num)
{
	num++;
	printf("Quit: 3\n");
}

void	ft_sigint_handler_here_doc(int num)
{
	num++;
	exit(1);
}

void	ft_sigquit_handler_here_doc(int num)
{
	num++;
	return ;
}
