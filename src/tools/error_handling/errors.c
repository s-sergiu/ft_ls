#include "ft_ls.h"

void	send_error(int code, char c)
{
	if (code == ILLEGAL_FLAG)
	{
		ft_printf("ls: invalid option -- '%c'\n", c);
		ft_printf("Try 'ls --help' for more information.\n");
		exit(2);
	}
}

