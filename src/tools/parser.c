#include "ft_ls.h"

// Store a path if valid;
// Print error if invalid, dont exit;
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

// First it parses flags;
// Second parses arguments (location);
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

// Check if valid flag, if invalid exit immediately
//
// **argv:	entire main arguments
// index:	index of the argument (always > 1);
int		is_valid_flag(const char **argv, int index)
{
	int		offset;
	int		flag_index;
	char	valid_flags[6] = {'l', 'R', 'a', 'r', 't', 0};

	offset = 1;
	flag_index = 0;
	if (!argv)
		return (1);
	while (argv[index][offset])
	{
		while (valid_flags[flag_index])
		{
			if (valid_flags[flag_index] == argv[index][offset])
				break ;
			flag_index++;
		}
		if (!valid_flags[flag_index])
			send_error(ILLEGAL_FLAG, argv, index, offset);
		flag_index = 0;
		offset++;
	}
	return (0);
}
