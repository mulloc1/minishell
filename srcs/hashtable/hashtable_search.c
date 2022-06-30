/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:01:23 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/30 17:09:31 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

char	*hashtable_search(t_hashtable *table, char *key)
{
	unsigned long long	hashcode;
	t_hashtable_data	*data;
	size_t				idx;
	t_list				*temp;

	if (!key)
		return (NULL);
	hashcode = hashcode_making(key);
	idx = hashcode % table->size;
	data = table->hashtable[idx].top->content;
	if (table->hashtable[idx].size == 1)
	{
		if (!ft_strncmp(key, data->key, ft_strlen(key) + 1))
			return (data->value);
	}
	else if (table->hashtable[idx].size > 1)
	{
		temp = key_overlap_check(table->hashtable[idx].top, key);
		if (temp)
			return (((t_hashtable_data *)temp->content)->value);
	}
	return (NULL);
}
