#include "ft_ls.h"

// store a path if valid
// print error if invalid, dont exit
int		store_paths(const char **arg, int i, int argc)
{
	DIR*	stream;
	int		path_index;
	char**	paths;
	int		exit_status;

	path_index = 0;
	exit_status = 0;
	stream = opendir(arg[i]);
	paths = (char **)malloc(sizeof(char *) * argc);
	if (!stream)
	{
		if (arg[i][0] == '-')
			send_error(errno, arg, i, 2);
		send_error(errno, arg, i, 0);
		exit_status = 2;
	}
	else
	{
		paths[path_index] = ft_strdup(arg[i]);
		path_index++;
	}
	(void)paths;
	return (exit_status);
}	

// first if parses flags
// second parses arguments (location);
int		handle_args(const char **argv, int argc)
{
	int		index;
	int		exit_status;

	index = 1;
	exit_status = 0;
	if (!argv[index])
		return (0);
	while (argv[index])
	{
		if (argv[index][0] == '-' && ft_isalnum(argv[index][1]))
		{
			is_valid_flag(argv, index);
			argc--;
		}
		index++;
	}
	index = 1;
	if (argc == index)
		return (0);
	while (argv[index])
	{
		exit_status = store_paths(argv, index, argc);
		index++;
	}

	return (exit_status);
}

// check if valid flag, if invalid exit immediately
int		is_valid_flag(const char **argv, int index)
{
	int		i;
	int		j;
	char	valid_flags[6] = {'l', 'R', 'a', 'r', 't', 0};

	i = 1;
	j = 0;
	if (!argv)
		return (1);
	while (argv[index][i])
	{
		while (valid_flags[j] && valid_flags[j] != argv[index][i])
			j++;
		if (!valid_flags[j])
			send_error(ILLEGAL_FLAG, argv, index, i);
		j = 0;
		i++;
	}
	return (0);
}
