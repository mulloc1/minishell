/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:24:51 by jaebae            #+#    #+#             */
/*   Updated: 2022/07/06 12:34:17 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define PRINT 1
# define NOT_PRINT 0

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
	NOT_VALID = 1,
	IS_DIR,
	PM_DENIED,
	IN_PUT_ERR,
	SPACE
};

typedef struct s_token
{
	int		type;
	char	*token;
}			t_token;

typedef struct s_tree_node
{
	t_token				data;
	int					visited;

	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

typedef struct s_tree
{
	struct s_tree_node	*root;
}						t_tree;

typedef struct s_init_struct
{
	t_hashtable	*table;
	t_list		*list;
	t_tree		*tree;
	char		**envp;
	char		**split_path;
}	t_init_struct;

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
	char		**split_path;
}	t_cmd;
// bintree
t_tree			*create_bin_tree(t_tree_node root_node);
t_tree_node		*insert_left_node(t_tree_node *parent, t_tree_node child);
t_tree_node		*insert_right_node(t_tree_node *parent, t_tree_node child);
void			delorder(t_tree_node **node);
void			delete_tree(t_tree *tree);
void			ft_error(char *str);
// parsing line
t_init_struct	*init(int argc, char *envp[]);
t_hashtable		*init_hashtable(void);
char			**ft_split_pipe(char const *s, char c);
void			ft_quote_shift(char const *s, int *idx);
t_tree			*ft_parser(char *str);
int				ft_end_env(char *key, char *token, int point);
// command exec
void			ft_search_tree(t_tree_node *node, t_cmd	*cmd);
void			ft_cmd_run(t_cmd *cmd);
void			ft_set_fd(t_cmd *cmd);
void			ft_get_path(t_cmd *cmd);
void			ft_open_pipe(t_cmd *cmd, t_tree_node *node);
int				ft_visit_cmd(t_token token, t_cmd *cmd);
int				ft_visit_double_redi_left(t_token token, t_cmd *cmd);
int				ft_visit_double_redi_right(t_token token, t_cmd *cmd);
int				ft_visit_redi_left(t_token token, t_cmd *cmd);
int				ft_visit_redi_right(t_token token, t_cmd *cmd);
int				ft_visit(t_token token, t_cmd *cmd);
char			*ft_check_eof(char *eof);
void			ft_read_parsing(char *eof, t_cmd *cmd);
void			ft_create_split_path(t_cmd *cmd);
void			ft_modify_split_path(t_cmd *cmd);
void			ft_check_path(t_cmd *cmd, char *check_path);
void			ft_check_join_path(t_cmd *cmd, char *env_path, char *path_tmp);
char			**ft_split_argv(char *token, t_hashtable *table);
void			dredi_l_check(t_tree_node *tree);
void			null_guard(void *ptr);
// builtin
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
void			ft_pop_envp(char **envp, char *name);
void			ft_modify_envp(t_cmd *cmd, char *str, char *new_key);
// signal
void			ft_set_signal(void (*sig_int)(int), void (*sig_quit)(int));
void			ft_set_echoctl(int flag);
//signal handler
void			ft_sigint_handler(int num);
void			ft_sigint_handler_wait_child(int num);
void			ft_child_sigint_handler(int num);
void			ft_sigquit_handler(int num);
void			ft_sigquit_handler_wait_child(int num);
void			ft_child_sigquit_handler(int num);
// macros
int				ft_is_signal_end(int status);
int				ft_get_signal_num(int status);
int				ft_exit_status(int status);
int				ft_is_dir(unsigned short st_mode);
int				ft_is_file(unsigned short st_mode);
void			ft_ascii_art(void);

#endif
