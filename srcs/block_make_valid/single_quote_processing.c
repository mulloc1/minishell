/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_processing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:15:49 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/01 13:41:05 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "hashtable.h"
#include "env.h"
#include <stdlib.h>

int	single_quote_processing(char **block, int idx)
{
	char	*temp;
	int		temp_idx;
	int		backup_idx;
	int		backup2_idx;

	temp = ft_strdup(*block);
	temp_idx = idx;
	backup_idx = idx;
	while ((*block)[++idx])
	{
		if ((*block)[idx] != (*block)[backup_idx])
			temp[temp_idx++] = (*block)[idx];
		else
			break ;
	}
	backup2_idx = temp_idx;
	while ((*block)[++idx])
		temp[temp_idx++] = (*block)[idx];
	temp[temp_idx] = '\0';
	free(*block);
	*block = temp;
	return (backup2_idx - backup_idx);
}
