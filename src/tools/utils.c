
#include "ft_ls.h"

void	list_dirs(void (*f)(void *))
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

void	add_file_to_list(struct dirent *entry)
{
	struct s_dir*	dir_list;

	dir_list = s_dir_return_head();
	if (entry->d_name[0] == '.')
		return ;
	if (s_dir_push(&dir_list, entry->d_name) < 0)
		return ;
}

struct dirent*	scan_dir(DIR *stream)
{
	struct dirent*	entry;

	entry = readdir(stream);
	if (!entry)
		return (NULL);
	add_file_to_list(entry);
	return 	(scan_dir(stream));
}

void	print_item(void *item) 
{
	struct stat		file_stats;

	stat(STDOUT, &file_stats);
	if (file_stats.st_rdev != 0)
		ft_printf("%s  ", item);
	else
		ft_printf("%s\n", item);
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
		scan_dir(stream);
	closedir(stream);
	list_dirs(print_item);
	if (file_stats.st_rdev != 0)
		ft_printf("\n");
	s_dir_sort_alphabetically(list);
	s_dir_free_memory(list);
}
