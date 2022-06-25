/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list_remove.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:22:54 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/25 21:39:21 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_env_list.h"

int	sort_env_list_remove(t_list **list, char *key)
{
	t_list	*temp;
	t_list	*temp2;
	int		key_len;

	key_len = ft_strlen(key);
	temp = *list;
	if (!ft_strncmp(key, (*list)->content, key_len + 1))
	{
		*list = (*list)->next;
		free(temp);
		return (1);
	}
	while (temp->next)
	{
		if (!ft_strncmp(key, temp->next->content, key_len + 1))
		{
			temp2 = temp->next;
			temp->next = temp->next->next;
			free(temp2);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
