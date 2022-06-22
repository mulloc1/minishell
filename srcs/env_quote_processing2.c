/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:12:18 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/23 01:14:53 by mulloc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"

char	*check_env(char *temp, int idx)
{
	char	*res;
	char	quote;
	int		i;

	// null을 리턴 안해줌
	quote = temp[idx];
	res = ft_calloc(50, sizeof(char));
	while (temp[idx] != '$' && temp[idx])
		idx++;
	if (temp[idx] != '$')
		return (NULL);
	i = -1;
	while (temp[++idx] != ' ' && temp[idx] && temp[idx] != '\"')
		res[++i] = temp[idx];
	return (res);
}

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

int	double_quote_processing(t_tree_node *node, int idx, t_hashtable *hashtable)
{
	char	*key;
	char	*value;
	char	*temp; char	*temp2;
	int		temp_idx;
	int		backup_idx;
	int		i;
	int		j;
	int		z;

	temp_idx = idx;
	backup_idx = idx;
	temp = node->data.token;
	while (1)
	{
		key = check_env(temp, idx);
		if (!key)
			break ;
		value = hashtable_search(hashtable, key);
		temp2 = ft_calloc(ft_strlen(temp) + ft_strlen(value), sizeof(char));
		i = -1;
		while (temp[++i] != '$')
			temp2[i] = temp[i];
		z = i;
		j = -1;
		while (value[++j])
			temp2[i++] = value[j];
		// 제대로 체크 안됨 공백 이외 다른것들도 있음
		while (temp[z++] != ' ' && temp[z] && temp[z] != '\\' && temp[z] != '\"' && temp[z] != '\'')
			;
		while (temp[z])
			temp2[++i] = temp[z++];
		free(value);
		free(key);
		free(temp);
		temp = temp2;
	}
	node->data.token = temp;
	single_quote_processing(node, idx);
	return (i);
}
