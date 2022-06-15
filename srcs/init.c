#include "hashtable.h"
#include "libft.h"
#include "minishell.h"
#include <signal.h>
#include <termios.h>

static t_hashtable *hashtable_init(char *envp[])
{
	t_hashtable	*table;
	char		**sp_envp;

	table = hashtable_create();
	while (*envp)
	{
		sp_envp = ft_split(*envp, '=');
		hashtable_insert(table, sp_envp[0], sp_envp[1]);
		envp++;	
	}
	return (table);
}

static char    **envp_init(char *envp[])
{
	char	**res;
	int		cnt;
	int		idx;

	cnt = -1;
    while (envp[++cnt])
		;
	res = malloc(cnt * sizeof(char *));
	if (!res)
		return (NULL);
	idx = -1;
	while (++idx < cnt)
	{
		res[idx] = ft_strdup(envp[idx]);
		if (!res[idx])
		{
			idx = -1;
			while (res[++idx])
				free(res[idx]);
			free(res);
			return (NULL);
		}
	}
	return (res);
}

static void	signal_init()
{
	signal(SIGINT, sigint_handler());
	signal(SIGQUIT, sigquit_handler());
	signal(SIGTERM, sigteam_handler());
}

t_init_struct   *init(int argc, char *envp[])
{
   t_init_struct    *init_struct;

   if (argc != 1)
	   exit(1);
   signal_init();
   init_struct = malloc(sizeof(t_init_struct *));
   if (!init_struct)
       return (NULL);
   init_struct->table = hashtable_init(envp);
   init_struct->envp = envp_init(envp);
   init_struct->tree = NULL;
   return (init_struct);
}
