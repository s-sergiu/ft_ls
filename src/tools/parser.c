#include "ft_ls.h"

int		store_paths(t_data** data, void* content)
{
	DIR*	stream;
	char*	arg;

	arg = content;
	stream = opendir(arg);
	if (!stream)
	{
		dir_error(errno, arg, (*data));
		(*data)->exit_status = BADDIR;
		return (BADDIR);
	}
	return (0);
}	

void	print_dirs(void* arg)
{
	char*	str;
	str = arg;
	if (str)
		printf("str: %s\n", str);
}

void	lst_remove_path(t_list** list, void* content)
{
	t_list*	temp;

	temp = *(list);
	while (temp)
	{
		if (temp->content == content)
		{
			free(temp->content);
			temp->content = NULL;
		}
		temp = temp->next;
	}
}

void	is_valid_flag_or_add_path(t_data* data, char *argv)
{
	if (argv[0] == '-' && ft_isalnum(argv[1]))
		is_valid_flag(argv);
	else
		ft_lstadd_back(&data->dirs, ft_lstnew(ft_strdup(argv)));
}

void	parse_path_list(t_data** data)
{
	t_list*	current;

	current = (*data)->dirs;
	while (current)
	{
		if (store_paths(data, current->content) == BADDIR)
			lst_remove_path(&current, current->content);
		current = current->next;
	}
}

void	handle_args(t_data* data)
{
	int		index;

	index = 1;
	while (data->argv[index])
	{
		is_valid_flag_or_add_path(data, data->argv[index]);
		index++;
	}
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
