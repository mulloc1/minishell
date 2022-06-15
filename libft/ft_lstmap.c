/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:55:56 by jaewchoi          #+#    #+#             */
/*   Updated: 2021/11/28 20:30:49 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static void	ft_lstapply(t_list *lst, void *(*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		temp->content = f(temp->content);
		temp = temp->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;

	if (!lst || !f)
		return (0);
	result = ft_lstnew(lst->content);
	if (!result)
		return (0);
	temp = result;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_lstnew((lst)->content);
		temp = temp->next;
		if (!temp)
		{
			ft_lstclear(&result, del);
			return (0);
		}
		lst = lst->next;
	}
	ft_lstapply(result, f);
	return (result);
}
