
#include "ft_ls.h"

void	s_dir_print_directory(t_dir* dir, void (*f)(void *))
{
	t_file*	index;

	index = dir->files;
	while (index)
	{
		f(index);
		index = index->next_entry;
	}
}

void	s_dir_add_file_to_head(t_dir** dir, struct dirent* entry)
{
	if (entry->d_name[0] == '.')
		return ;
	if (s_dir_push(dir, entry->d_name) < 0)
		return ;
}

t_dir*	scan_directory(DIR *stream)
{
	struct dirent*	entry;
	t_dir*			dir;

	dir = (t_dir*)malloc(sizeof(t_dir));
	dir->files = NULL;
	dir->size = 0;
	entry = readdir(stream);
	if (!entry)
		return (NULL);
	while (entry)
	{
		s_dir_add_file_to_head(&dir, entry);
		entry = readdir(stream);
	}
	return (dir);
}

int	is_output_a_terminal(void)
{
	struct stat	file_stats;

	stat(STDOUT, &file_stats);
	if (file_stats.st_rdev != 0)
		return (1);
	return (0);
}

void	print_element(void *item) 
{
	char*		filename;

	filename = ((t_file*)item)->name;
	if (is_output_a_terminal())
		ft_printf("%s  ", filename);
	else
		ft_printf("%s\n", filename);
}

void	execute(char **args)
{
	DIR*	stream;
	t_dir*	dir;

	stream = opendir(args[1]);
	(void)dir;
	if (!stream)
		return ;
	if (*args[1])
		dir = scan_directory(stream);
	closedir(stream);
	s_dir_print_directory(dir, print_element);
	if (is_output_a_terminal())
		ft_printf("\n");
	t_dir_free_memory(dir);
	free(dir);
}
