/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:03:26 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/08 17:49:20 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	key_search(t_list *top, char *key, t_list **del, t_list **prev)
{
	t_hashtable_data	*data;

	*del = NULL;
	*prev = NULL;
	if (!top)
		return ;
	data = top->content;
	if (!ft_strncmp(data->key, key, ft_strlen(key)))
	{
		*del = top;
		return ;
	}
	while (top->next && ft_strncmp(\
				((t_hashtable_data *)top->next->content)->key, \
				key, ft_strlen(key)))
		top = top->next;
	*prev = top;
	*del = top->next;
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
	t_list				*del;
	t_list				*prev;

	hashcode = hashcode_making(key);
	idx = hashcode % table->size;
	key_search(table->hashtable[idx].top, key, &del, &prev);
	if (!del)
		return (0);
	if (table->hashtable[idx].size == 1)
		table->hashtable[idx].top = NULL;
	else if (table->hashtable[idx].top == del)
		table->hashtable[idx].top = table->hashtable[idx].top->next;
	else if (prev && del)
		prev->next = del->next;
	else if (prev)
		prev->next = NULL;
	ft_lstdelone(del, del_node);
	table->hashtable[idx].size--;
	return (1);
}
