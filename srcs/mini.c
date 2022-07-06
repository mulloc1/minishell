/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:54:46 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/06 18:36:26 by jaebae           ###   ########.fr       */
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

void	dredi_l_check(t_tree_node *tree)
{
	t_tree_node	*redi;
	int			cnt;

	cnt = 0;
	while (tree)
	{
		redi = tree->left;
		while (redi)
		{
			if (redi->data.type == DREDI_L)
				cnt++;
			redi = redi->left;
		}
		tree = tree->right;
	}
	if (cnt > 16)
		ft_error("bash: maximum here-document count exceeded\n");
}

int	is_spaces(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	return (1);
}

void	syntax_error_check(t_init_struct *init_struct)
{
	t_tree_node	*cmd;
	t_tree_node	*redi;

	cmd = init_struct->tree->root;
	while (cmd)
	{
		redi = cmd->left;
		while (redi)
		{
			if (redi->data.token == NULL || redi->data.token[0] == '\0')
			{
				delete_tree(init_struct->tree);
				init_struct->tree = NULL;
				return ;
			}
			redi = redi->left;
		}
		if (is_spaces(cmd->data.token))
		{
			delete_tree(init_struct->tree);
			init_struct->tree = NULL;
			return ;
		}
		cmd = cmd->right;
	}
}

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
