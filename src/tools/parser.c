
#include "ft_ls.h"

// handle -l -R -a -r -t

void	store_arg(char *arg)
{
	DIR*	stream;

	ft_printf("arg: %s\n", arg);
	stream = opendir(arg);
	ft_printf("ft_ls: cannot access '%s': %s\n", arg, strerror(errno));
	(void)stream;
	
}	

int		handle_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			check_illegal_flag(argv[i] + 1);
		else
			store_arg(argv[i]);
		i++;
	}

	return (1);
}

void	check_illegal_flag(char *str)
{
	int		i;
	int		j;
	char	valid_flags[6] = {'l', 'R', 'a', 'r', 't', 0};

	i = 0;
	j = 0;
	while (str[i])
	{
		while (valid_flags[j] && valid_flags[j] != str[i])
			j++;
		if (!valid_flags[j])
			send_error(ILLEGAL_FLAG, str[i]);	
		j = 0;
		i++;
	}
}
