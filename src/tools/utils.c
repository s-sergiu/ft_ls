
#include "ft_ls.h"

int		get_number_of_files(char *args)
{
	DIR*			stream;
	int				i;
	
	if (!args)
		return (0);
	i = 0;
	stream = opendir(args);
	if (!stream)
		return (-1);
	while (readdir(stream))
		i++;
	closedir(stream);

	return (i);
}

void	add_file_to_array(char arr[][NAME_MAXLEN], struct dirent* entry, int i)
{
	size_t	str_size;

	str_size = ft_strlen(entry->d_name);
	ft_strlcpy(&arr[i][NAME], entry->d_name, str_size + 1);
	arr[i][STRLEN] = str_size;
	arr[i][FLAGS] = 0;
	if (entry->d_name[0] == '.')
		arr[i][FLAGS] |= FLAG_HIDDEN;
	else
		arr[i][FLAGS] |= FLAG_VISIBLE;
}

void	scan_directory(char arr[][NAME_MAXLEN], char *arg)
{
	struct dirent*	entry;
	DIR*			stream;
	int				i;

	i = 0;
	stream = opendir(arg);
	entry = readdir(stream);
	while (entry)
	{
		add_file_to_array(arr, entry, i);
		entry = readdir(stream);
		i++;
	}
	closedir(stream);
}

int		is_output_a_terminal(void)
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
			write(1, &arr[i][NAME], arr[i][STRLEN]);
			if (is_tty)
				write(1, "  ", 2); 
			else
				write(1, "\n", 1); 
		}
		i++;
	}
}

void	execute(char **argv)
{
	char	(*arr)[NAME_MAXLEN];
	int		size;

	size = get_number_of_files(argv[1]);
	arr = malloc(size * sizeof *arr);
	if (!arr)
		return ;
	scan_directory(arr, argv[1]);
	output_directory(arr);
	if (is_output_a_terminal())
		write(1, "\n", 1);
}
