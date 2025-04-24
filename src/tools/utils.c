
#include "ft_ls.h"

void	s_dir_print_directory(void (*f)(void *))
{
	struct s_dir*	index;
	struct s_dir*	dir_list;

	dir_list = s_dir_return_head();
	index = dir_list->head;
	while (index)
	{
		f(index);
		index = index->next_entry;
	}
}

void	s_dir_add_file_to_head(struct dirent *entry)
{
	struct s_dir*	dir_list;

	dir_list = s_dir_return_head();
	if (entry->d_name[0] == '.')
		return ;
	if (s_dir_push(&dir_list, entry->d_name) < 0)
		return ;
}

struct dirent*	scan_directory(DIR *stream)
{
	struct dirent*	entry;

	entry = readdir(stream);
	if (!entry)
		return (NULL);
	s_dir_add_file_to_head(entry);
	return 	(scan_directory(stream));
}

void	print_element(void *item) 
{
	struct stat	file_stats;
	char*		filename;

	filename = ((struct s_dir*)item)->file;
	stat(STDOUT, &file_stats);
	if (file_stats.st_rdev != 0)
		ft_printf("%s  ", filename);
	else
		ft_printf("%s\n", filename);
}

void	execute(char **args)
{
	DIR*			stream;
	struct stat		file_stats;
	struct s_dir*	list;

	list = s_dir_return_head();
	stat(STDOUT, &file_stats);
	stream = opendir(args[1]);
	if (!stream)
		return ;
	if (*args[1])
		scan_directory(stream);
	closedir(stream);
	s_dir_print_directory(print_element);
	if (file_stats.st_rdev != 0)
		ft_printf("\n");
	s_dir_sort_alphabetically(list);
	s_dir_free_memory(list);
}
