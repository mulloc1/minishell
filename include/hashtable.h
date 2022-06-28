/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:29:50 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/28 15:35:57 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H
# include "libft.h"

typedef struct s_hashtable_data
{
    char    *key;
    char    *value;
}           t_hashtable_data;

typedef struct s_hashtable_node
{
		t_list	*top;
		int		 size;
}				 t_hashtable_node;

typedef struct s_hashtable
{
		t_hashtable_node	*hashtable;
		int					 size;
}							 t_hashtable;

unsigned long long hashcode_making(char *str);
t_list  *key_overlap_check(t_list *top, char *key);
t_hashtable	*hashtable_create();
int		hashtable_insert(t_hashtable *table, char *key, char *value);
int 	hashtable_remove(t_hashtable *table, char *key);
// int		hashtable_delete(t_hashtable *table);
char	*hashtable_search(t_hashtable *table, char *key);

#endif
