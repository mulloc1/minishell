/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:12:18 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/22 20:50:15 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"

int	single_quote_processing(t_tree_node *node, int idx)
{
	char	*temp;
	char	*token;
	int		temp_idx;
	int		backup_idx;

	token = node->data.token;
	temp = ft_strdup(token);
	temp_idx = idx;
	backup_idx = idx;
	while (token[++idx])
	{
		if (token[idx] != token[backup_idx])
			temp[temp_idx++] = token[idx];
	}
	temp[temp_idx] = '\0';
	free(token);
	node->data.token = temp;
	return (temp_idx);
}

int	double_quote_processing(t_tree_node *node, int idx, t_hashtable_node *hashtable)
{
	char	*key;
	char	*value;
	char	*temp;
	char	*temp2;
	int		temp_idx;
	int		backup_idx;

	temp_idx = idx;
	backup_idx = idx;
	temp = ft_strdup(node->data.token);
	while (1)
	{
		key = check_env(node, idx);
		if (!key)
			break ;
		value = hashtable_search(hashtable, key);
		temp2 = ft_calloc(ft_strlen(temp) + ft_strlen(value), sizeof(char));
		free(value);
		free(key);
		free(temp);
	}
	single_quote_processing(t_tree_node *node, idx);
	return (0);
}
