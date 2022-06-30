/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_processing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:16:14 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/30 19:24:26 by jaebae           ###   ########.fr       */
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
	i--;
	while (temp[++i] != '$' && temp[i])
		temp2[i] = temp[i];
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
	int					point;
	int					i;

	point = 0;
	i = idx;
	while (1)
	{
		data.key = check_env(node->data.token, i);
		if (ft_end_env(data.key, node->data.token, point))
		{
			if (data.key)
				free(data.key);
			break ;
		}
		data.value = hashtable_search(hashtable, data.key);
		temp = processing(node->data.token, &data, &i, &point);
		free(data.key);
		free(node->data.token);
		node->data.token = temp;
	}
	point = single_quote_processing(node, idx);
	return (point);
}
