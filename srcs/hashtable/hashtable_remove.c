#include "hashtable.h"
#include "libft.h"
#include <stdlib.h>

static t_list  *key_search(t_list *top, char *key)
{
	if (!top)
		return (NULL);
	if (!ft_strncmp(((t_hashtable_data *)top->content)->key, key, ft_strlen(key)))
		return (top);
	while (!top && ft_strncmp(((t_hashtable_data *)top->next->content)->key, key, ft_strlen(key)))
		top = top->next;
	return (top);
}

static void	del_node(void *node)
{
	t_list  *temp;
	t_list  *del_node;

	if (!node)
		return ;
	temp = (t_list *)node;
	if (!temp->next)
		del_node = temp;
	else
	{
		del_node = temp->next;
		temp->next = temp->next->next;
	}
	free(((t_hashtable_data *)del_node->content)->key);
	free(((t_hashtable_data *)del_node->content)->value);
	free(del_node->content);
	free(del_node);
}

int hashtable_remove(t_hashtable *table, char *key)
{
	unsigned long long  hashcode;
	unsigned int		idx;
	t_list			  *temp;

	hashcode = hashcode_making(key);
	idx = hashcode % table->size;
	temp = key_search(table->hashtable[idx].top, key);
	if (!temp)
		return (0);
	if (table->hashtable[idx].size == 1)
		table->hashtable[idx].top = NULL;
	if (table->hashtable[idx].top == temp)
		table->hashtable[idx].top = table->hashtable[idx].top->next;
	ft_lstdelone(temp, del_node);
	table->hashtable[idx].size--;
	return (1); 
}

