/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_processing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:15:49 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/27 15:59:17 by mulloc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"

int	single_quote_processing(t_tree_node *node, int idx)
{
	char	*temp;
	char	*token;
	int		temp_idx;
	int		backup_idx;
	int		backup2_idx;

	token = node->data.token;
	temp = ft_strdup(token);
	temp_idx = idx;
	backup_idx = idx;
	while (token[++idx])
	{
		if (token[idx] != token[backup_idx])
			temp[temp_idx++] = token[idx];
		else
			break ;
	}
	backup2_idx = temp_idx;
	while (token[++idx])
		temp[temp_idx++] = token[idx];
	temp[temp_idx] = '\0';
	free(token);
	node->data.token = temp;
	return (backup2_idx - backup_idx);
}
