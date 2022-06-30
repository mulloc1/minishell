/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:24:33 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/30 18:24:43 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_ENV_LIST_H
# define SORT_ENV_LIST_H

# include "libft.h"

void	sort_env_list_insert(t_list **list, char *key);
int		sort_env_list_remove(t_list **list, char *key);

#endif
