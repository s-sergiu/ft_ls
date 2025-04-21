#include "ft_ls.h"

struct s_dir*	get_directory_list(void)
{
	static struct s_dir	directory;

	return &directory;
}

void	list_dirs(void (*f)(void *))
{
	struct s_dir	*index;
	struct s_dir*	dir_list;

	dir_list = get_directory_list();
	index = dir_list->head;
	while (index->next)
	{
		f(index->file);
		index = index->next;
	}
}

struct s_dir*	s_dir_new(char *name)
{
	struct s_dir	*new;
	new = (struct s_dir*)malloc(sizeof(struct s_dir));
	if (!new || !name)
		return (NULL);
	ft_strlcat(new->file, name, ft_strlen(name - 1));
	new->next = NULL;
	return (new);
}

void	s_dir_add_front(struct s_dir** dir_list, struct s_dir* file) 
{
	if ((*dir_list)->head == NULL)
		file->next = *dir_list;
	else
		file->next = (*dir_list)->head;
	(*dir_list)->head= file;
}

void	add_file_to_list(struct dirent *entry)
{
	struct s_dir	*dir_list;

	dir_list = get_directory_list();
	if (entry->d_name[0] == '.')
		return ;
	s_dir_add_front(&dir_list, s_dir_new(entry->d_name));
}

struct dirent*	scan_dir(DIR *stream)
{
	struct dirent	*entry;

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

	stat(STDOUT, &file_stats);
	stream = opendir(args[1]);
	if (!stream)
		return ;
	if (*args[1])
		scan_dir(stream);
	list_dirs(print_item);
	if (file_stats.st_rdev != 0)
		ft_printf("\n");
}
