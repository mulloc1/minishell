/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quote_processing2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:12:18 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/23 16:27:04 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"

int	ft_isnaming(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c == '-')
		return (1);
	else
		return (0);
}

char	*check_env(char *temp, int idx)
{
	char	*res;
	int		i;

	res = ft_calloc(50, sizeof(char));
	while (temp[idx] != '$' && temp[idx])
		idx++;
	if (temp[idx] != '$' || temp[idx + 1] == '\0' || temp[idx + 1] == ' ' || temp[idx + 1] == '\"')
		return (NULL);
	i = -1;
	while (ft_isnaming(temp[++idx]) && temp[idx])
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

char	*processing(char *temp, t_hashtable_data *data, int *i)
{
	char	*temp2;
	int		z;
	int		j;

	temp2 = ft_calloc(ft_strlen(temp) + ft_strlen((*data).value) + 1, sizeof(char));
	while (temp[++(*i)] != '$')
		temp2[*i] = temp[*i];
	z = *i;
	j = -1;
	while ((*data).value[++j])
		temp2[(*i)++] = (*data).value[j];
	while ((temp[z] == '$' || ft_isnaming(temp[z])) && temp[z])
	{
		if (temp[z] == '$' && (temp[z + 1] == ' ' || temp[z + 1] == '\0' || temp[z + 1] == '\"'))
			break ;
		z++;
	}
	while (temp[z])
		temp2[(*i)++] = temp[z++];
	return (temp2);
}

int	double_quote_processing(t_tree_node *node, int idx, t_hashtable *hashtable)
{
	t_hashtable_data	data;
	char				*temp; 
	char				*temp2;
	int					i;

	temp = node->data.token;
	while (1)
	{
		data.key = check_env(temp, idx);
		if (!data.key)
			break ;
		data.value = hashtable_search(hashtable, data.key);
		i = -1;
		temp2 = processing(temp, &data, &i);	
		free(data.key);
		free(temp);
		temp = temp2;
	}
	node->data.token = temp;
	single_quote_processing(node, idx);
	return (i);
}
