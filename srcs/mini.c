/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:54:46 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/08 15:28:42 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "hashtable.h"
#include "parser.h"
#include "libft.h"

static void	ft_run(char *str, t_init_struct *init_struct)
{
	if (str && str[0] != '\0')
	{
		add_history(str);
		if (str[0] != '|')
			init_struct->tree = ft_parser(str);
		if (init_struct->tree)
		{
			dredi_l_check(init_struct->tree->root);
			syntax_error_check(init_struct);
		}
		ft_excution(init_struct);
		if (init_struct->tree)
		{
			delete_tree(init_struct->tree);
			init_struct->tree = NULL;
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_init_struct	*init_struct;
	char			*str;

	argv++;
	ft_ascii_art();
	ft_set_signal(ft_sigint_handler, ft_sigquit_handler);
	ft_set_echoctl(NOT_PRINT);
	init_struct = init(argc, envp);
	while (1)
	{
		str = readline("minishell$ ");
		if (!is_spaces(str))
			ft_run(str, init_struct);
		if (str)
			free(str);
		else
		{
			printf("\033[1A\033[11Cexit\n");
			ft_set_echoctl(PRINT);
			exit(0);
		}
	}
	return (0);
}
