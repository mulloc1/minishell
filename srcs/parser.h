#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int	ft_search_redirect(char *str);
int	ft_redirection_case(char *cmd, int *i);
t_token	ft_redirection_token_make(char *cmd, int i);
void	ft_pipe_tree_parsing(char *cmd, t_tree_node *left, t_tree_node *right);
t_tree	*ft_parser(char *str);

#endif