/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list_insert.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulloc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 09:36:54 by mulloc            #+#    #+#             */
/*   Updated: 2022/06/25 13:31:27 by mulloc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_env_list.h"

void	sort_env_list_insert(t_list **list, char *key)
{
	t_list	*temp;
	t_list	*new;
	int		key_len;

	key_len = ft_strlen(key);
	new = ft_lstnew(key);
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	temp = *list;
	if (ft_strncmp(key, (char *)temp->content, key_len + 1) == -1)
	{
		new->next = *list;
		*list = new;
		return ;
	}
	while (temp->next)
	{
		if (ft_strncmp(key, (char *)temp->next->content, key_len + 1) == -1)
		{
			new->next = temp->next;
			temp->next = new;
			return ;
		}
		temp = temp->next;
	}
	if (ft_strncmp(key, (char *)temp->content, key_len + 1) == 1)
		temp->next = new;
	else 
		free(new);
}
