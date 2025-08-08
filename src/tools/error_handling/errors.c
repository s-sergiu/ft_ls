#include "ft_ls.h"

void	send_error(int code, char **arg, int i, int offset)
{
	if (code == ENOENT)
	{
		ft_putstr_fd(arg[0] + 2, 2);
		write(2, ": cannot access '", 17);
		ft_putstr_fd(arg[i], 2);
		perror("'");
		if (offset == 2)
			exit(offset);
	}

	if (code == ILLEGAL_FLAG)
	{
		write(2, "ft_ls: invalid option -- '", 26);
		ft_putstr_fd(arg[i] + offset, 2);
		write(2, "'\n", 2);
		write(2, "Try 'ls --help' for more information.\n", 38);
		exit(2);
	}
}
