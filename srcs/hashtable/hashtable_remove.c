/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:03:26 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/08 15:04:58 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft.h"
#include <stdlib.h>

static t_list	*key_search(t_list *top, char *key)
{
	t_hashtable_data	*data;

	if (!top)
		return (NULL);
	data = top->content;
	if (!ft_strncmp(data->key, key, ft_strlen(key)))
		return (top);
	while (!top && ft_strncmp(\
				((t_hashtable_data *)top->next->content)->key, \
				key, ft_strlen(key)))
		top = top->next;
	return (top);
}

static void	del_node(void *node)
{
	t_list	*temp;

	if (!node)
		return ;
	temp = (t_list *)node;
	free(((t_hashtable_data *)temp->content)->key);
	free(((t_hashtable_data *)temp->content)->value);
	free(temp->content);
	free(temp);
}

int	hashtable_remove(t_hashtable *table, char *key)
{
	unsigned long long	hashcode;
	unsigned int		idx;
	t_list				*temp;
	t_list				*temp2;

	hashcode = hashcode_making(key);
	idx = hashcode % table->size;
	temp = key_search(table->hashtable[idx].top, key);
	if (!temp)
		return (0);
	if (table->hashtable[idx].size == 1)
		table->hashtable[idx].top = NULL;
	if (table->hashtable[idx].top == temp)
		table->hashtable[idx].top = table->hashtable[idx].top->next;
	else
	{
		temp2 = temp->next;
		temp->next = temp->next->next;
		temp = temp2;
	}
	ft_lstdelone(temp, del_node);
	table->hashtable[idx].size--;
	return (1);
}
