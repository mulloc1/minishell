#include "minishell.h"

int	ft_visit(t_token token, t_cmd *cmd)
{
	if (token.type == CMD)
		return (ft_visit_cmd(token, cmd));
	else if (token.type == REDI_L)
		return (ft_visit_redi_left(token, cmd));
	else if (token.type == REDI_R)
		return (ft_visit_redi_right(token, cmd));
	else if (token.type == DREDI_L)
		return (ft_visit_double_redi_left(token, cmd));
	else
		return (ft_visit_double_redi_right(token, cmd));
}
