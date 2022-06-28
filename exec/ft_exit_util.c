#include "libft.h"
#include <stdlib.h>

int	ft_exit_error(char *argv)
{
	char	*err_msg;
	int		exit_status;

	if (argv)
	{
		err_msg = ": numeric argument required";
		exit (255);
	}
	else
	{
		err_msg = "too many arguments";
		exit_status = 1;
	}
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putendl_fd(err_msg, 2);
	return (exit_status);
}

void	ft_check_exit_status(char *num)
{
	unsigned long	result;
	unsigned long	long_max;
	int				i;
	int				minus;

	result = 0;
	minus = 0;
	i = -1;
	if (num[0] == '+' || num[0] == '-')
		i++;
	if (num[0] == '-')
		minus = 1;
	long_max = LONG_MAX;
	while (num[++i])
	{
		if (!ft_isdigit(num[i]))
			(unsigned char)ft_exit_error(num);
		result = (result * 10) + (num[i] - '0');
		if ((!minus && result > long_max) || (minus && result > long_max + 1))
			(unsigned char)ft_exit_error(num);
	}
	exit ((unsigned char)result);
}
