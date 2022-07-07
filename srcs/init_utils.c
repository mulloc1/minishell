/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:17:12 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/07 16:26:36 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

void	increase_str_int(char **value)
{
	int	num;

	num = ft_atoi(*value);
	if (num == 1000)
		num = 1;
	else
		num++;
	free(*value);
	*value = ft_itoa(num);
}

void	increase_shlvl(char **env)
{
	char	**env_split;
	char	*temp;

	if (!(*env))
		return ;
	env_split = ft_export_split(*env);
	if (!env_split)
		ft_error("increase_shlvl env_split failed");
	free(*env);
	increase_str_int(&env_split[1]);
	temp = ft_strjoin(env_split[0], "=");
	if (!temp)
		ft_error("increase_shlvl temp ft_join failed");
	free(env_split[0]);
	env_split[0] = temp;
	*env = ft_strjoin(env_split[0], env_split[1]);
	if (!(*env))
		ft_error("increase_shlvl env ft_join failed");
	free(env_split[0]);
	free(env_split[1]);
	free(env_split);
}
