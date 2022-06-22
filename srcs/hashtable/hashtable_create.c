#include "hashtable.h"
#include "libft.h"
#include <stdlib.h>

t_hashtable *hashtable_create()
{
    t_hashtable *table;
	int			i;

    table = malloc(sizeof(t_hashtable));
    if (!table)
        return (NULL);
    table->hashtable = ft_calloc(100, sizeof(t_hashtable_node));
    if (!table->hashtable)
    {
        free(table);
        return (NULL);
    }
	i = -1;
	while (++i < 100)
	{
		table->hashtable[i].top = NULL;
		table->hashtable[i].size = 0;
	}
    table->size = 100;
    return (table);
}


