/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:17:30 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/01 14:14:55 by jaebae           ###   ########.fr       */
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
	int		j;

	temp2 = ft_calloc(ft_strlen(temp) + \
			ft_strlen(data->value) + 1, sizeof(char));
	i = -1;
	while (++i < *idx)
		temp2[i] = temp[i];
	i--;
	while (temp[++i] != '$' && temp[i])
		temp2[i] = temp[i];
	j = -1;
	if (data->value)
		while (data->value && data->value[++j])
			temp2[i++] = data->value[j];
	*idx = i;
	*point = i + 1;
	j = i - j;
	while ((temp[j] == '$' || ft_isnaming(temp[j])) && temp[j])
		j++;
	while (temp[j])
		temp2[i++] = temp[j++];
	return (temp2);
}

int	not_quote_processing(char **block, int idx, t_hashtable *hashtable)
{
	t_hashtable_data	data;
	char				*temp;
	int					point;
	int					i;

	point = 0;
	i = idx;
	while ((*block)[i] && !quote_check(&(*block)[i]))
	{
		if ((*block)[i] == '$')
		{
			data.key = check_env(*block, i);
			if (ft_end_env(data.key, *block, point))
				break ;
			data.value = hashtable_search(hashtable, data.key);
			temp = processing(*block, &data, &i, &point);
			free(data.key);
			free(*block);
			*block = temp;
		}
		else
			i++;
	}
	return (i - idx);
}
