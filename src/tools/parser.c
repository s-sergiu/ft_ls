#include "ft_ls.h"

// Store a path if valid;
// Print error if invalid, dont exit;
int		store_paths(char **arg, int i)
{
	DIR		*stream;
	int		exit_status;

	exit_status = 0;
	stream = opendir(arg[i]);
	if (!stream)
	{
		if (arg[i][0] == '-')
			send_error(errno, arg, i, 2);
		send_error(errno, arg, i, 0);
		exit_status = 2;
	}
	return (exit_status);
}	

void	print_dirs(void* arg)
{
	char*	str;
	str = arg;
	printf("str: %s\n", str);
}
// First it parses flags. If it encounters an invalid flag it exits code 2;
// Then it resets the index of the arguments and starts parsing them to see if
// they are paths and they are valid.
int		handle_args(t_data* data)
{
	int		index;
	char	**parsed_args;

	parsed_args = data->argv;
	index = 1;
	while (parsed_args[index])
	{
		if (parsed_args[index][0] == '-' && ft_isalnum(parsed_args[index][1]))
		{
			is_valid_flag(parsed_args, index);
			// free null and reset pointer
			// will not work with arrays I think
		}
		else
			ft_lstadd_back(&data->dirs, ft_lstnew(parsed_args[index]));
		index++;
	}
	index = 1;
	while (parsed_args[index])
	{
		if (parsed_args[index][0] == '-' && ft_isalnum(parsed_args[index][1]))
		{
			if (is_valid_flag(parsed_args, index) != 0)
				data->exit_status = store_paths(parsed_args, index);
		}
		else
			data->exit_status = store_paths(parsed_args, index);
		index++;
	}

	return (data->exit_status);
}

// Check if valid flag, if invalid exit immediately
//
// **argv:	entire main arguments
// index:	index of the argument (always > 1);
int		is_valid_flag(char **argv, int index)
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
