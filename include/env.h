#ifndef ENV_H
# define ENV_H
# include "minishell.h"
# include "hashtable.h"

# define NOT_QUOTE 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

int		export_check(char *token);
int		quote_check(char *token);
void	env_quote_processing(t_init_struct	*init_struct);
int		ft_isnaming(char c);
char	*check_env(char *temp, int idx);
int		single_quote_processing(t_tree_node *node, int idx);
int		double_quote_processing(t_tree_node *node, int idx, t_hashtable *table);
int		not_quote_processing(t_tree_node *node, int idx, t_hashtable *table);

#endif
