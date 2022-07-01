/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:17:21 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/01 14:05:23 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

t_hashtable	*hashtable_create(void)
{
	t_hashtable	*table;
	int			i;

	table = malloc(sizeof(t_hashtable));
	if (!table)
		ft_error("hashtable_create() t_hashtable malloc failed");
	table->hashtable = ft_calloc(100, sizeof(t_hashtable_node));
	if (!table->hashtable)
	{
		free(table);
		ft_error("hashtable_create() t_hashtable_node malloc failed");
	}
	i = -1;
	while (++i < 100)
	{
		table->hashtable[i].top = NULL;
		table->hashtable[i].size = 0;
	}
	table->size = 100;
	return (table);
}
