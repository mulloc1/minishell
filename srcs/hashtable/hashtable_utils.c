/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:57:13 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/08 17:37:20 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashtable.h"
#include <stdio.h>

unsigned long long	hashcode_making(char *key)
{
	unsigned long	hashcode;
	int				i;

	hashcode = 0;
	i = -1;
	while (key[++i])
	{
		hashcode += key[i];
		if (key[i + 1])
			hashcode *= 11;
	}
	return (hashcode);
}

t_list	*key_overlap_check(t_list *top, char *key)
{
	if (!top)
		return (NULL);
	while (top && ft_strncmp(\
				((t_hashtable_data *)top->content)->key, \
				key, ft_strlen(key) + 1))
		top = top->next;
	return (top);
}
