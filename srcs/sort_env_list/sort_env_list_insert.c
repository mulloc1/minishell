/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list_insert.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 09:36:54 by mulloc            #+#    #+#             */
/*   Updated: 2022/06/30 14:53:25 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_env_list.h"
#include <stdlib.h>

void	sort_env_list_insert(t_list **list, char *key)
{
	t_list	*temp;
	t_list	*new;
	int		key_len;
	int		cmp_res;

	key_len = ft_strlen(key);
	new = ft_lstnew(ft_strdup(key));
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	temp = *list;
	cmp_res = ft_strncmp(key, (char *)temp->content, key_len + 1);
	if (cmp_res == -1)
	{
		new->next = *list;
		*list = new;
		return ;
	}
	else if (cmp_res == 0)
	{
		free(new->content);
		free(new);
		return ;
	}
	while (temp->next)
	{
		cmp_res = ft_strncmp(key, (char *)temp->next->content, key_len + 1);
		if (cmp_res == -1)
		{
			new->next = temp->next;
			temp->next = new;
			return ;
		}
		else if (cmp_res == 0)
		{
			free(new->content);
			free(new);
			return ;
		}
		temp = temp->next;
	}
	cmp_res = ft_strncmp(key, (char *)temp->content, key_len + 1);
	if (cmp_res == 1)
		temp->next = new;
	else 
	{
		free(new->content);
		free(new);
	}		
}
