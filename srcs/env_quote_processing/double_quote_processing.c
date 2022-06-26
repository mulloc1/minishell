/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_processing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:16:14 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/26 16:49:48 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"

static char	*processing(char *temp, t_hashtable_data *data, int *idx, int *point)
{
	char	*temp2;
	int		i;
	int		z;
	int		j;

	temp2 = ft_calloc(ft_strlen(temp) + ft_strlen((*data).value) + 1, sizeof(char));
	i = -1;
	while (temp[++i] != '$' && temp[i] && i <= *idx)
		temp2[i] = temp[i];
	z = i;
	j = -1;
	while ((*data).value[++j])
		temp2[i++] = (*data).value[j];
	*idx = i;
	*point = i + 1;
	while ((temp[z] == '$' || ft_isnaming(temp[z])) && temp[z])
	{
		if (temp[z] == '$' && (temp[z + 1] == ' ' || temp[z + 1] == '\0' || temp[z + 1] == '\"'))
			break ;
		z++;
	}
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
		if (!data.key || !temp[point] || (point > 0 && (temp[point + 1] == '\"' || temp[point + 1] == '\'')))
			break ;
		data.value = hashtable_search(hashtable, data.key);
		temp2 = processing(temp, &data, &i, &point);	
		free(data.key);
		free(temp);
		temp = temp2;
	}
	node->data.token = temp;
	single_quote_processing(node, idx);
	return (point - idx - 1);
}
