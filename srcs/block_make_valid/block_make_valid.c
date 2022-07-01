/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:00:25 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/01 14:11:48 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"
#include <stdlib.h>

char	*block_make_valid(char *block, t_hashtable *table)
{
	char	*temp;
	int		status;
	int		i;

	i = 0;
	temp = ft_strdup(block);
	while (temp[i])
	{
		status = quote_check(&temp[i]);
		if (status == SINGLE_QUOTE)
			i += single_quote_processing(&temp, i);
		else if (status == DOUBLE_QUOTE)
			i += double_quote_processing(&temp, i, table);
		if (status == NOT_QUOTE)
			i += not_quote_processing(&temp, i, table);
	}
	return (temp);
}
