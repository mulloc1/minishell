/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_quote_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:17:30 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/06 18:14:57 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"
#include <stdlib.h>

static void	something(char **block, int *idx)
{
	if (*(*block + *idx + 1) == '\'' || *(*block + *idx + 1) == '\"')
		ft_memmove(*block + *idx, *block + *idx + 1, ft_strlen(*block) - *idx);
	else
		*idx += 1;
}

static int	init_j(int j, int i)
{
	if (j == -1)
		return (i);
	else
		return (i - j);
}

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
	j = init_j(j, i);
	while (ft_isnaming(&temp[++j]) && temp[j])
		if (j > 1 && temp[j - 2] == '$' && temp[j - 1] == '?')
			break ;
	while (temp[j])
		temp2[i++] = temp[j++];
	return (temp2);
}

static int	ft_end_not_quote(char *key, char **block, int point, int *i)
{
	if (ft_end_env(key, *block, point))
	{
		something(block, i);
		return (1);
	}
	else
		return (0);
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
			if (ft_end_not_quote(data.key, block, point, &i))
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
