/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:09:52 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/06 13:14:07 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	content_free(t_list *node)
{
	if (node->content)
	{
		if (((t_hashtable_data *)node->content)->key)
			free(((t_hashtable_data *)node->content)->key);
		if (((t_hashtable_data *)node->content)->value)
			free(((t_hashtable_data *)node->content)->value);
		free(node->content);
	}
}

static char	*value_allocate(char *value)
{
	if (value)
		return (ft_strdup(value));
	else
		return (NULL);
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
	data->value = value_allocate(value);
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
