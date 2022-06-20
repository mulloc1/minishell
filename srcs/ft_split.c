/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:07:00 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/20 14:11:50 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_quote_shift(char *str, int idx)
{

}

int	ft_word_cnt(char *str, char sep)
{
	
}

char	**ft_split(char	*str, char sep)
{
	int		word_cnt;
	
	word_cnt = ft_word_cnt(str, sep);
}

int main(void)
{
	char	**cmds;

	cmds = ft_split("cat \"ls -l | cat < echo\" > file1 | cat", '|');

	int i = -1;
	while (cmds[++i])
		printf("%s\n", cmds[i]);
	return (0);
}
