#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include "hashtable.h"
# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1
# define P_READ 0
# define P_WRITE 1
# define STDIN 0
# define STDOUT 1
# define VALID 1


enum e_builtins
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_token_type
{
	CMD = 0,
	REDI_L,
	REDI_R,
	DREDI_L,
	DREDI_R
};

enum e_cmd_state
{
	NOT_VALID = 1, // 127
	IS_DIR, // 126
	PM_DENIED, // 126
	IN_PUT_ERR, // 1
	SPACE
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
	t_list		*list;
    t_tree      *tree;
    char        **envp;
}               t_init_struct;

typedef struct s_cmd
{
	char		*path;
	char		**argv;
	char		**envp;
	int			in_fd;
	int			out_fd;
	int			pipe[2];
	pid_t		last_pid;
	int			builtins;
	int			is_pipe;
	int			path_state;
	t_hashtable	*table;
	t_list		*env_list;
}	t_cmd;

t_tree			*create_bin_tree(t_tree_node root_node);
t_tree_node		*insert_left_node(t_tree_node *parent, t_tree_node child);
t_tree_node		*insert_right_node(t_tree_node *parent, t_tree_node child);
void			delorder(t_tree_node **node);
void			delete_tree(t_tree *tree);
void			ft_error(char *str);

t_init_struct	*init(int argc, char *envp[]);
t_hashtable		*init_hashtable();
char			**ft_split_mini(char const *s, char c);
void			ft_quote_shift(char const *s, int *idx);
t_tree			*ft_parser(char *str);
void			env_quote_processing(t_init_struct	*init_struct);
int				double_quote_processing(t_tree_node *node, int idx, t_hashtable *hashtable);
int				single_quote_processing(t_tree_node *node, int idx);

void	ft_search_tree(t_tree_node *node, t_cmd	*cmd);
void	ft_cmd_run(t_cmd *cmd);
void	ft_get_path(t_cmd *cmd);
void	ft_open_pipe(t_cmd *cmd, t_tree_node *node);
int		ft_visit_cmd(t_token token, t_cmd *cmd);
int		ft_visit_double_redi_left(t_token token, t_cmd *cmd);
int		ft_visit_double_redi_right(t_token token, t_cmd *cmd);
int		ft_visit_redi_left(t_token token, t_cmd *cmd);
int		ft_visit_redi_right(t_token token, t_cmd *cmd);
int		ft_visit(t_token token, t_cmd *cmd);
char	*ft_check_eof(char *eof);
void	ft_read_parsing(char *eof, t_cmd *cmd);
void	ft_create_path_list(t_cmd *cmd);
void	ft_delete_path_list(void *list);
void	ft_check_path(t_cmd *cmd, char *check_path);
void	ft_check_join_path(t_cmd *cmd, char *env_path, char *path_tmp);

int				ft_add_env(t_cmd *cmd);
void			ft_builtin_run(t_cmd *cmd);
void			ft_cd(t_cmd *cmd);
char			*ft_check_eof(char *eof);
void			ft_echo(t_cmd *cmd);
void			ft_env(t_cmd *cmd);
int				ft_exit_error(char *argv);
void			ft_check_exit_status(char *num);
void			ft_exit(t_cmd *cmd);
void			ft_export_error(char *name, int type);
int				ft_check_name_valid(char *name, int type);
void			ft_export_print(t_cmd *cmd);
char			**ft_export_split(char *src);
void			ft_export(t_cmd *cmd);
void			ft_pwd(t_cmd *cmd);
void			ft_unset(t_cmd *cmd);
void			ft_excution(t_init_struct *init_struct);
char			**ft_split_argv(char *token, t_hashtable *table)

#endif
