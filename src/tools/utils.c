
#include "ft_ls.h"

int	count_files_inside_dir(DIR *stream)
{
	struct dirent*	entry;
	int				i;
	
	i = 0;
	entry = readdir(stream);
	if (!entry)
		return (-1);
	while (entry)
	{
		entry = readdir(stream);
		i++;
	}
	return (i);
}

void	add_file_to_array(char arr[][NAME_MAXLEN], struct dirent* entry, int i)
{
	size_t	str_size;
	str_size = ft_strlen(entry->d_name);
	ft_strlcpy(&arr[i][2], entry->d_name, str_size + 1);
	arr[i][STRLEN] = str_size;
	arr[i][FLAGS] = 0;
	if (entry->d_name[0] == '.')
		arr[i][FLAGS] |= FLAG_HIDDEN;
	else
		arr[i][FLAGS] |= FLAG_VISIBLE;
}

void	scan_directory(char arr[][NAME_MAXLEN], DIR *stream)
{
	struct dirent*	entry;
	int				i;

	entry = readdir(stream);
	if (!entry)
		return ;
	i = 0;
	while (entry)
	{
		add_file_to_array(arr, entry, i);
		entry = readdir(stream);
		i++;
	}
	arr[i][0] = 0;
}

int	is_output_a_terminal(void)
{
	struct stat	file_stats;

	stat(STDOUT, &file_stats);
	if (file_stats.st_rdev != 0)
		return (1);
	return (0);
}

void	output_directory(char arr[][NAME_MAXLEN])
{
	int i;
	int is_tty;
	
	i = 0;
	is_tty = is_output_a_terminal();
	while(arr[i][STRLEN])
	{
		if (arr[i][FLAGS] & FLAG_VISIBLE)
		{
			write(1, &arr[i][2], arr[i][STRLEN]);
			if (is_tty)
				write(1, "  ", 2); 
			else
				write(1, "\n", 1); 
		}
		i++;
	}
}

void	execute(char **args)
{
	DIR*	stream;
	int		dir_size;
	char	(*arr)[NAME_MAXLEN];

	stream = opendir(args[1]);
	dir_size = count_files_inside_dir(stream);
	closedir(stream);
	arr = malloc(dir_size * sizeof *arr);
	stream = opendir(args[1]);
	if (*args[1])
		scan_directory(arr, stream);
	closedir(stream);
	output_directory(arr);
	//print_debug_info();
	if (is_output_a_terminal())
		write(1, "\n", 1);
}
