#include "hashtable.h"
#include "libft.h"
#include <stdlib.h>

t_hashtable *hashtable_create()
{
    t_hashtable *table;

    table = malloc(sizeof(t_hashtable));
    if (!table)
        return (NULL);
    table->hashtable = ft_calloc(100, sizeof(t_hashtable_node));
    if (!table->hashtable)
    {
        free(table);
        return (NULL);
    }
    table->size = 100;
    return (table);
}


