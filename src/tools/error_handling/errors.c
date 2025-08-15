#include "ft_ls.h"

void	dir_error(int code, char* arg, t_data* data)
{
	char*	main;

	main = data->argv[0] + 2;
	if (code == ENOENT)
	{
		ft_putstr_fd(main , 2);
		write(2, ": cannot access '", 17);
		ft_putstr_fd(arg, 2);
		perror("'");
	}
}

void	flag_error(int code, char *arg, int i)
{
	if (code == ILLEGAL_FLAG)
	{
		write(2, "ft_ls: invalid option -- '", 26);
		write(2, &arg[i], 1);
		write(2, "'\n", 2);
		write(2, "Try 'ls --help' for more information.\n", 38);
		exit(BADFLAG);
	}
}
