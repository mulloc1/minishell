/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:09:52 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/30 17:15:01 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	content_free(t_list *node)
{
	free(((t_hashtable_data *)node->content)->key);
	free(((t_hashtable_data *)node->content)->value);
	free(node->content);
}

int	hashtable_insert(t_hashtable *table, char *key, char *value)
{
	unsigned long long	hashcode;
	unsigned int		idx;
	t_hashtable_data	*data;
	t_list				*node;

	if (!key || !table)
		return (0);
	hashcode = hashcode_making(key);
	idx = hashcode % table->size;
	data = ft_calloc(1, sizeof(t_hashtable_data));
	null_guard(data);
	data->key = ft_strdup(key);
	data->value = ft_strdup(value);
	node = key_overlap_check(table->hashtable[idx].top, data->key);
	if (node)
	{
		content_free(node);
		node->content = data;
	}
	else
	{
		ft_lstadd_back(&table->hashtable[idx].top, ft_lstnew((void *)data));
		table->hashtable[idx].size++;
	}
	return (1);
}
