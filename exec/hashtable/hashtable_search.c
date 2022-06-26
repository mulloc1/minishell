#include "hashtable.h"

char	 *hashtable_search(t_hashtable *table, char *key)
{
	unsigned long long	hashcode;
	size_t				idx;
    t_list              *temp;

    if (!key)
        return (NULL);
	hashcode = hashcode_making(key);
	idx = hashcode % table->size;
	if (table->hashtable[idx].size == 1)
	    return (((t_hashtable_data *)table->hashtable[idx].top->content)->value);
    else if (table->hashtable[idx].size > 1)
    {
        temp = key_overlap_check(table->hashtable[idx].top, key);
        if (temp)
            return (((t_hashtable_data *)temp->content)->value); 
    }
    return (NULL);
}
