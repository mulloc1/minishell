/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list_insert.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 09:36:54 by mulloc            #+#    #+#             */
/*   Updated: 2022/07/06 14:27:46 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_env_list.h"
#include <stdlib.h>

void	tree_free(t_list *node)
{
	free(node->content);
	free(node);
}

static int	top_node_insert(t_list **list, t_list *new, char *key, int key_len)
{
	int	temp;

	temp = ft_strncmp(key, (char *)((*list)->content), key_len + 1);
	if (temp == -1)
	{
		new->next = *list;
		*list = new;
		return (1);
	}
	else if (temp == 0)
	{
		tree_free(new);
		return (1);
	}
	return (0);
}

static int	mid_node_insert(t_list *list, t_list *new, char *key, int key_len)
{
	int	temp;

	temp = ft_strncmp(key, (char *)((*list).next->content), key_len + 1);
	if (temp == -1)
	{
		new->next = list->next;
		list->next = new;
		return (1);
	}
	else if (temp == 0)
	{
		tree_free(new);
		return (1);
	}
	return (0);
}

void	sort_env_list_insert(t_list **list, char *key)
{
	t_list	*temp;
	t_list	*new;
	int		key_len;

	key_len = ft_strlen(key);
	new = ft_lstnew(ft_strdup(key));
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	if (top_node_insert(list, new, key, key_len + 1))
		return ;
	temp = *list;
	while (temp->next)
	{
		if (mid_node_insert(temp, new, key, key_len + 1))
			return ;
		temp = temp->next;
	}
	if (ft_strncmp(key, (char *)temp->content, key_len + 1) == 1)
		temp->next = new;
	else
		tree_free(new);
}
