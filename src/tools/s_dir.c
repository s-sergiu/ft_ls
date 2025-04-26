
#include "ft_ls.h"

int	s_dir_is_empty(struct s_dir *node)
{
	(void)node;
	return (!node->size);
}

struct s_dir*	s_dir_return_head(void)
{
	static struct	s_dir	directory;

	if (!directory.next_entry)
		directory.size = 0;
	return (&directory);
}

struct s_dir*	s_dir_new(const char *name)
{
	struct s_dir*	new;
	new = (struct s_dir*)malloc(sizeof(struct s_dir));
	if (!new || !name)
		return (NULL);
	new->file[0] = 0;
	new->head = NULL;
	ft_strlcat(new->file, name, ft_strlen(name) + 1);
	new->next_entry = NULL;
	return (new);
}

int	s_dir_pop(struct s_dir** dir_list)
{
	if ((*dir_list)->size == 0)
		return -1;
	(*dir_list)->size--;
	return (1);
}

int	s_dir_push(struct s_dir** dir_list, const char *name) 
{
	struct s_dir*	file;

	if (!(*dir_list))
		return (-1);
	file = s_dir_new(name);
	if ((*dir_list)->head != NULL)
		file->next_entry = (*dir_list)->head;
	(*dir_list)->head= file;
	(*dir_list)->size++;
	return (1);
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

int	s_dir_free_memory(struct s_dir* list)
{
	struct s_dir	*index;
	struct s_dir	*temp;

	if (list->head)
		index = list->head;
	while (index)
	{
		temp = index->next_entry;
		free(index);
		index = temp;
	}
	return (1);
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
