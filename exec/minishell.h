#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1
# define P_READ 0
# define P_WRITE 1
# define STDIN 0
# define STDOUT 1


#include <stdio.h>

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

typedef struct s_cmd
{
	char	*path;
	char	**argv;
	char	**envp;
	int		in_fd;
	int		out_fd;
	int		pipe[2];
	pid_t	last_pid;
	int		builtins;
}	t_cmd;


t_tree		*create_bin_tree(t_tree_node root_node);
t_tree_node	*insert_left_node(t_tree_node *parent, t_tree_node child);
t_tree_node	*insert_right_node(t_tree_node *parent, t_tree_node child);
void		delorder(t_tree_node **node);
void		delete_tree(t_tree *tree);
void		ft_error(char *str);

void	ft_search_tree(t_tree_node *node, t_cmd	*cmd);
void	ft_cmd_run(t_cmd *cmd);
char	*ft_get_path(char *str, char **envp);
void	ft_open_pipe(t_cmd *cmd, t_tree_node *node);
int		ft_visit_cmd(t_token token, t_cmd *cmd);
int		ft_visit_double_redi_left(t_token token, t_cmd *cmd);
int		ft_visit_double_redi_right(t_token token, t_cmd *cmd);
int		ft_visit_redi_left(t_token token, t_cmd *cmd);
int		ft_visit_redi_right(t_token token, t_cmd *cmd);
int		ft_visit(t_token token, t_cmd *cmd);
char	*ft_check_eof(char *eof);
void	ft_pasing_multiline(char *eof, int out_fd);

#endif