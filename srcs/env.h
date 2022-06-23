#ifndef ENV_H
# define ENV_H
# include "minishell.h"
# include "hashtable.h"

int		export_check(char *token);
int		quote_check(char *token);
void	env_quote_processing(t_init_struct	*init_struct);
int		ft_isnaming(char c);
char	*check_env(char *temp, int idx);
int		single_quote_processing(t_tree_node *node, int idx);
char	*processing(char *temp, t_hashtable_data *data, int *i);

#endif
