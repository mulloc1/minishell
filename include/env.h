/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:28:52 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/03 22:02:38 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "minishell.h"
# include "hashtable.h"

# define NOT_QUOTE 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

int		export_check(char *token);
int		quote_check(char *token);
int		ft_isnaming(char *c);
char	*check_env(char *temp, int idx);
int		single_quote_processing(char **block, int idx);
int		double_quote_processing(char **block, int idx, t_hashtable *table);
int		not_quote_processing(char **block, int idx, t_hashtable *table);
char	*block_make_valid(char *block, t_hashtable *table);

#endif
