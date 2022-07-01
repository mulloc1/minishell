#include "libft.h"
#include "minishell.h"
#include "sort_env_list.h"
#include "hashtable.h"
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

void	display(t_hashtable *table, t_list *list)
{
	while (list)
	{
		printf("%s=%s\n", list->content, hashtable_search(table, (char *)list->content));
		list = list->next;
	}
	printf("\n");
}

int main(int argc, char *argv[], char *envp[])
{
	argv++;
	t_init_struct *init_struct = init(argc, envp);
	display(init_struct->table, init_struct->list);
	sort_env_list_remove(&init_struct->list, "COLORFGBG");
	sort_env_list_remove(&init_struct->list, "LANG");
	sort_env_list_remove(&init_struct->list, "SHLVL");
	sort_env_list_remove(&init_struct->list, "TERM");
	sort_env_list_remove(&init_struct->list, "TERM_PROGRAM");
	sort_env_list_remove(&init_struct->list, "USER");
	display(init_struct->table, init_struct->list);
	system("leaks a.out");
	return (0);
}
