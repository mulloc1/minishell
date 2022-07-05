/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:13:24 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 12:13:24 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
