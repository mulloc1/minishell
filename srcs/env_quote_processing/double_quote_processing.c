/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_processing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:16:14 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/30 17:22:11 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"
#include <stdlib.h>

static char	*processing(char *temp, \
		t_hashtable_data *data, int *idx, int *point)
{
	char	*temp2;
	int		i;
	int		z;
	int		j;

	temp2 = ft_calloc(ft_strlen(temp) + \
			ft_strlen(data->value) + 1, sizeof(char));
	i = -1;
	while (++i <= *idx)
		temp2[i] = temp[i];
	while (temp[i] != '$' && temp[i])
	{
		temp2[i] = temp[i];
		i++;
	}
	z = i;
	j = -1;
	if (data->value)
		while (data->value && data->value[++j])
			temp2[i++] = data->value[j];
	*idx = i;
	*point = i;
	while ((temp[z] == '$' || ft_isnaming(temp[z])) && temp[z])
		z++;
	while (temp[z])
		temp2[i++] = temp[z++];
	return (temp2);
}

int	double_quote_processing(t_tree_node *node, int idx, t_hashtable *hashtable)
{
	t_hashtable_data	data;
	char				*temp;
	char				*temp2;
	int					point;
	int					i;

	temp = node->data.token;
	point = 0;
	i = idx;
	while (1)
	{
		data.key = check_env(temp, i);
		if (!data.key || !temp[point] || \
				(point > 0 && (temp[point] == '\"' || temp[point + 1] == '\"')))
		{
			if (data.key)
				free(data.key);
			break ;
		}
		data.value = hashtable_search(hashtable, data.key);
		temp2 = processing(temp, &data, &i, &point);
		free(data.key);
		free(temp);
		temp = temp2;
	}
	node->data.token = temp;
	point = single_quote_processing(node, idx);
	return (point);
}
