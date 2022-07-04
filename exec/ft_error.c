#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	ft_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	ft_set_echoctl(PRINT);
	exit(1);
}
