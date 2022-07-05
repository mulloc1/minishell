/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macro.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewchoi <jaewchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:20:08 by jaewchoi          #+#    #+#             */
/*   Updated: 2022/07/05 17:39:59 by jaewchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_signal_end(int status)
{
	return ((status & 0177) != 0177 && (status & 0177) != 0);
}

int	ft_get_signal_num(int status)
{
	return (status & 0177);
}

int	ft_exit_status(int status)
{
	return (status >> 8 & 0x000000ff);
}

int	ft_is_dir(unsigned short st_mode)
{
	return ((st_mode & 0170000) == 0040000);
}

int	ft_is_file(unsigned short st_mode)
{
	return ((st_mode & 0170000) == 0100000);
}
