#include "hashtable.h"
#include "libft.h"
#include <stdlib.h>

int hashtable_insert(t_hashtable *table, char *key, char *value)
{
	unsigned long long  hashcode;
	unsigned int		idx;
	t_hashtable_data	*data;
	t_list			  *node;

	if (!key || !table)
		return (0);
	hashcode = hashcode_making(key);
	idx = hashcode % table->size;
	data = ft_calloc(1, sizeof(t_hashtable_data));
	if (!data)
		return (0);
	data->key = ft_strdup(key);
	data->value = ft_strdup(value);
	node = key_overlap_check(table->hashtable[idx].top, data->key);
	if (node)
	{
		free(((t_hashtable_data *)node->content)->key);
		free(((t_hashtable_data *)node->content)->value);
		free(node->content);
		node->content = data;
	}
	else
	{
		ft_lstadd_back(&table->hashtable[idx].top, ft_lstnew((void *)data));
		table->hashtable[idx].size++;
	}
	return (1);
}
