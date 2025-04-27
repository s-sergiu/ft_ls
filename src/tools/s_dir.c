
#include "ft_ls.h"

/*
struct s_dir*	s_dir_return_head(void)
{
	static struct	s_dir	directory;

	if (!directory.next_entry)
		directory.size = 0;
	return (&directory);
}

unsigned int	s_dir_get_size(struct s_dir* dir)
{
	int				i;

	i = 0;
	if(!dir->head)
		return (0);
	dir = dir->head;
	while (dir)
	{
		i++;
		dir = dir->next_entry;
	}
	return (i);
}

int	s_dir_is_sorted(struct s_dir* list)
{
	struct s_dir*	index;
	char*			str1;
	char*			str2;

	if (!list->head)
		return (1);
	index = list->head;
	while (index->next_entry)
	{
		str1 = index->file;
		str2 = index->next_entry->file;
		if (ft_strncmp(str1, str2, ft_strlen(str1)) < 0)
			return (0);
		index = index->next_entry;
	}
	return (1);
}

void	s_dir_print_list(struct s_dir *list)
{
	struct s_dir*	index;
	int				i;

	i = 0;
	index = list->head;
	while(index)
	{
		ft_printf("file[%d]: %s\n", i, index->file);
		i++;
		index = index->next_entry;
	}
}

struct s_dir*	s_dir_init(void)
{
	struct s_dir*	new;
	new = (struct s_dir*)malloc(sizeof(struct s_dir));
	if (!new)
		return (NULL);
	new->file[0] = 0;
	new->head = NULL;
	new->next_entry = NULL;
	return (new);
}

size_t	get_list_size(struct s_dir *dir)
{
	int				i;

	i = 1;
	if(!dir)
		return (0);
	while (dir)
	{
		i++;
		dir = dir->next_entry;
	}
	return (i);
}

void	print_list(struct s_dir *list)
{
	int				i;
	struct s_dir*	index;

	i = 0;
	index = list;
	while(index)
	{
		ft_printf("file[%d]: %s\n", i, index->file);
		i++;
		index = index->next_entry;
	}
}

int	s_dir_sort_alphabetically(struct s_dir* list)
{
	size_t	size;
	size = s_dir_get_size(list) + 1;
	if (size < 2)
		return (1);
	(void)list;
	return (size);
}
*/

t_file*	t_file_new(const char *name)
{
	t_file*	new;

	if(!name[0])
		return (NULL);
	new = (t_file*)malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->name[0] = 0;
	new->next_entry = NULL;
	ft_strlcat(new->name, name, ft_strlen(name) + 1);
	return (new);
}

int	s_dir_push(t_dir** dir, const char *name) 
{
	t_file*	file;

	if (!dir || !(*dir))
		return (-1);
	file = t_file_new(name);
	if (!file)
		return (-1);
	file->next_entry = (*dir)->files;
	(*dir)->files= file;
	(*dir)->size++;
	return (1);
}

int	s_dir_pop(t_dir** dir)
{
	if ((*dir)->size == 0)
		return -1;
	(*dir)->size--;
	return (1);
}

int	s_dir_is_empty(t_dir* dir)
{
	(void)dir;
	return (!dir->size);
}

int	t_dir_free_memory(t_dir* dir)
{
	t_file*	file;
	t_file*	temp;

	file = dir->files;
	while (file)
	{
		temp = file->next_entry;
		free(file);
		file = temp;
	}
	return (1);
}

