#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	ft_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	exit(1);
}
