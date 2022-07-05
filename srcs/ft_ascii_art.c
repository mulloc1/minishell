/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ascii_art.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:52:46 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 21:10:32 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	ft_ascii_art(void)
{
	char	text[3000];
	int		size;
	int		fd;

	fd = open("murloc1.txt", O_RDONLY);
	size = read(fd, text, 3000);
	close(fd);
	text[size] = '\0';
	printf("\033[0;31m%s\n", text);
	fd = open("murloc2.txt", O_RDONLY);
	size = read(fd, text, 3000);
	close(fd);
	text[size] = '\0';
	printf("\033[0;32m%s\033[0;34m @jaewchoi @jaebae\n", text);
	fd = open("murloc3.txt", O_RDONLY);
	size = read(fd, text, 3000);
	close(fd);
	text[size] = '\0';
	printf("\033[0;32m%s\033[0m", text);
}
