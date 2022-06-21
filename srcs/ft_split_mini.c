/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaebae <jaebae@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:07:00 by jaebae            #+#    #+#             */
/*   Updated: 2022/06/21 10:52:14 by jaebae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#define	TEST1 "echo \"ls -l | cat > file1\"| cat \"Hello World\""
#define	TEST2 "echo \"hello > file1 | echo HELLO | ls -l"
#define	TEST3 "echo \'\"echo $PATH hAHAHH\"\' | ls -l"
#define	TEST4 "echo echo $PATH HAHAHAH\" | ls -l"
#define	TEST5 "ls -al > file1"
#define	TEST6 "cat < file1"
#define TEST7 "echo hello > file1 > file2"
#define TEST8 "cat > file2 < file1"
#define TEST9 "cat < file2 < file1"
#define TEST10 "echo hello >> file1 > file2"

#include "libft.h"
#include <stdio.h>

void	ft_quote_shift(char const *s, int *idx)
{
	int	i;

	i = 0;
	while (s[++i + *idx])
	{
		if (s[*idx] == s[*idx + i])
		{
			*idx += i;
			break ;
		}
	}
}

static int	ft_word_cnt(char const *s, char c)
{
	int	i;
	int	flag;
	int	cnt;

	i = -1;
	flag = 0;
	cnt = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			ft_quote_shift(s, &i);
		if (s[i] != c && flag == 0)
		{
			cnt++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
	}
	return (cnt);
}

static char	*ft_word_create(char const *s, char *c, int *idx)
{
	char	*result;	
	int		len;
	int		i;

	len = -1;
	while (!ft_strchr(c, s[*idx + ++len]))
	{
		if (s[*idx + len] == '\"' || s[*idx + len] == '\'')
			ft_quote_shift(s + *idx, &len);
	} result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = s[i + *idx];
	*idx += len;
	return (result);
}

char	**ft_split_mini(char const *s, char c)
{
	int		word_cnt;
	int		i;
	int		j;
	char	**result;
	char	sep[2];

	if (!s)
		return (NULL);
	word_cnt = ft_word_cnt(s, c);
	sep[0] = c;
	sep[1] = '\0';
	result = ft_calloc(word_cnt + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < word_cnt)
	{
		while (ft_strchr(sep, s[j]))
			j++;
		result[i] = ft_word_create(s, sep, &j);
	}
	return (result);
}
//
//void	display(char **cmds)
//{
//	int	i = -1;
//	while (cmds && cmds[++i])
//		printf("%s\n", cmds[i]);
//	printf("\n");
//}
//
//void	test(char	*str)
//{
//	char	**cmds;
//	printf("=================== %s ===================\n", str);
//	cmds = ft_split(str, '|');
//	display(cmds);
//}
//
//int main(void)
//{
//	test(TEST1);
//	test(TEST2);
//	test(TEST3);
//	test(TEST4);
//	test(TEST5);
//	test(TEST6);
//	test(TEST7);
//	test(TEST8);
//	test(TEST9);
//	test(TEST10);
//	return (0);
//}
