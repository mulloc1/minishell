#include "libft.h"
#include <stdlib.h>

void	ft_exit_error(char *argv)
{
	char	*err_msg;
	int		exit_status;

	if (argv)
	{
		err_msg = ": numeric argument required";
		exit_status = 255;
	}
	else
	{
		err_msg = "too many arguments";
		exit_status = 1;
	}
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putendl_fd(err_msg, 2);
	exit(exit_status);
}

unsigned char	ft_get_exit_status(char *num)
{
	unsigned long	result;
	int				i;
	int				minus;

	result = 0;
	minus = 0;
	i = -1;
	if (num[0] == '+' || num[0] == '-')
		i++;
	if (num[0] == '-')
		minus = 1;
	while (num[++i])
	{
		if (!ft_isdigit(num[i]))
			ft_exit_error(num);
		result = (result * 10) + (num[i] - '0');
		if ((!minus && result > LONG_MAX) || (minus && result > LONG_MAX + 1))
			ft_exit_error(num);
	}
	return ((unsigned char)result);
}
