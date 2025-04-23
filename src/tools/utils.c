#include "ft_ls.h"

unsigned char	is_empty(struct s_dir *node)
{
	(void)node;
	return (!node->size);
}
struct s_dir*	get_directory_list(void)
{
	static struct s_dir	directory;

	if (!directory.next_entry)
		directory.size = 0;
	return (&directory);
}

void	list_dirs(void (*f)(void *))
{
	struct s_dir*	index;
	struct s_dir*	dir_list;

	dir_list = get_directory_list();
	index = dir_list->head;
	while (index->next_entry)
	{
		f(index->file);
		index = index->next_entry;
	}
}

struct s_dir*	s_dir_new(const char *name)
{
	struct s_dir*	new;
	new = (struct s_dir*)malloc(sizeof(struct s_dir));
	if (!new || !name)
		return (NULL);
	ft_strlcat(new->file, name, ft_strlen(name - 1));
	new->next_entry = NULL;
	return (new);
}

int	s_dir_pop(struct s_dir** dir_list)
{
	if ((*dir_list)->size == 0)
		return -1;
	(*dir_list)->size--;
	return -1;
}

int	s_dir_push(struct s_dir** dir_list, const char *name) 
{
	if (!(*dir_list))
		return (-1);
	struct s_dir*	file;
	file = s_dir_new(name);
	if ((*dir_list)->head == NULL)
		file->next_entry = *dir_list;
	else
		file->next_entry = (*dir_list)->head;
	(*dir_list)->head= file;
	(*dir_list)->size++;
	return (0);
}

void	s_dir_sort_alphabetically(struct s_dir* list)
{
	(void)list;
	struct s_dir*	temp = NULL;
	char*			str1;
	char*			str2;
	str1 = (list->head)->file;
	str2 = (list->head)->next_entry->file;
	ft_printf("address %p\n", temp);
	temp = (struct s_dir*)malloc(sizeof(struct s_dir));

	ft_printf("strncmp %d\n", ft_strncmp(str2, str1, ft_strlen(str1)));
	ft_printf("address %s\n", (list->head)->next_entry->file);
	ft_printf("address %p\n", temp);
}

void	add_file_to_list(struct dirent *entry)
{
	struct s_dir*	dir_list;

	dir_list = get_directory_list();
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

	list = get_directory_list();
	stat(STDOUT, &file_stats);
	stream = opendir(args[1]);
	if (!stream)
		return ;
	if (*args[1])
		scan_dir(stream);
	list_dirs(print_item);
	if (file_stats.st_rdev != 0)
		ft_printf("\n");
	s_dir_sort_alphabetically(list);
}
