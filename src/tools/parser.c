#include "ft_ls.h"

// Store a path if valid;
// Print error if invalid, dont exit;
int		store_paths(t_data* data, void* content)
{
	DIR*	stream;
	char*	arg;

	arg = content;
	stream = opendir(arg);
	if (!stream)
	{
		dir_error(errno, arg, data, 0);
		return (2);
	}
	return (0);
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

	index = 1;
	while (data->argv[index])
	{
		if (data->argv[index][0] == '-' && ft_isalnum(data->argv[index][1]))
		{
			is_valid_flag(data->argv[index]);
			// free null and reset pointer
			// will not work with arrays I think
		}
		else
			ft_lstadd_back(&data->dirs, ft_lstnew(data->argv[index]));
		index++;
	}
	index = 1;
	while (data->dirs)
	{
		if (store_paths(data, data->dirs->content) == 2)
		{
			data->exit_status = 2;
			//remove item from list;
		}
		data->dirs = data->dirs->next;
	}

	return (data->exit_status);
}

int		validated_flag(char flag)
{
	int		index;
	char	valid_flags[6] = {'l', 'R', 'a', 'r', 't', 0};

	index = 0;
	while (valid_flags[index])
	{
		if (valid_flags[index] == flag)
			return (0);
		index++;
	}
	return (1);
}

// Check if valid flag, if invalid exit immediately
//
// **argv:	entire main arguments
// index:	index of the argument (always > 1);

int		is_valid_flag(char *argv)
{
	int		index;

	index = 1;
	if (!argv)
		return (1);
	while (argv[index])
	{
		if (!validated_flag(argv[index]))
			index++;
		else
			flag_error(ILLEGAL_FLAG, argv, index);
	}
	return (0);
}
