#ifndef MINISHELL_H
# define MINISHELL_H

# include "hashtable.h"

enum e_token_type
{
	CMD = 0,
	REDI_L,
	REDI_R,
	DREDI_L,
	DREDI_R
};

typedef struct s_token
{
	int		type;
	char	*token;
}			t_token;

typedef struct s_tree_node
{
	t_token	data;
	int		visited;

	struct s_tree_node	*left;
	struct s_tree_node	*right;
} t_tree_node;

typedef struct s_tree
{
	struct s_tree_node	*root;
} t_tree;

typedef struct s_init_struct
{
    t_hashtable *table;
    t_tree      *tree;
    char        **envp;
}               t_init_struct;

t_tree			*create_bin_tree(t_tree_node root_node);
t_tree_node		*insert_left_node(t_tree_node *parent, t_tree_node child);
t_tree_node		*insert_right_node(t_tree_node *parent, t_tree_node child);
t_hashtable		*init_hashtable();
void			delete_tree(t_tree *tree);
void			ft_error(char *str);
t_init_struct	*init(int argc, char *envp[]);
char			**ft_split_mini(char const *s, char c);
void			ft_quote_shift(char const *s, int *idx);

#endif
