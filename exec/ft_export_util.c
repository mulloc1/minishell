#include "libft.h"

void	ft_export_error(char *name, int type)
{
	char	*cmd;

	if (type)
		cmd = "export: `";
	else
		cmd = "unset: `";
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
}

int	ft_check_name_valid(char *name, int type)
{
	int i;

	if (!ft_isalpha(name[0]))
	{
		ft_export_error(name, type);
		return (0);
	}
	i = 0;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]))
		{
			ft_export_error(name, type);
			return (0);
		}
	}
	return (1);
}
