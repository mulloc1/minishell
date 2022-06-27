/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:17:30 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/27 19:48:54 by mulloc           ###   ########.fr       */
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

	temp2 = ft_calloc(ft_strlen(temp) + ft_strlen(data->value) + 1, sizeof(char));
	i = -1;
	while (++i <= *idx)
		temp2[i] = temp[i];
	i--;
	while (temp[i] != '$' && temp[i])
	{
		temp2[i] = temp[i];
		i++;
	}
	z = i;
	j = -1;
	while (data->value && data->value[++j])
		temp2[i++] = data->value[j];
	*idx = i;
	*point = i + 1;
	// env가 공백없이 존재할 때
	// shift 함수 작성
	while ((temp[z] == '$' || ft_isnaming(temp[z])) && temp[z])
	{
		if (temp[z] == '$' && (temp[z + 1] == ' ' || temp[z + 1] == '\0' || temp[z + 1] == '\"' || temp[z + 1] == '\''))
			break ;
		z++;
	}
	while (temp[z])
		temp2[i++] = temp[z++];
	return (temp2);
}

int	not_quote_processing(t_tree_node *node, int idx, t_hashtable *hashtable)
{
	t_hashtable_data	data;
	char				*token;
	char				*temp;
	int					point;
	int					i;

	token = node->data.token;
	point = 0;
	i = idx;
	while (token[i] && token[i] != '\'' && token[i] != '\"')
	{
		if (token[i] == '$')
		{
			data.key = check_env(token, i);
			if (!data.key || !token[point] || (point > 0 && (token[point + 1] == '\"' || token[point + 1] == '\'')))
				break ;
			data.value = hashtable_search(hashtable, data.key);
			temp = processing(token, &data, &i, &point);	
			free(data.key);
			free(token);
			data.value = NULL;
			token = temp;
		}
		else
			i++;
	}
	node->data.token = token;
	return (i - idx);	
}
