
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

int	copy_dir_into_array(struct s_dir *list, char (*array)[128], int size)
{
	int		i;

	i = 0;
	list = list->head;
	while (list && i < size)
	{
		ft_strlcpy(array[i], list->file, ft_strlen(list->file) + 1);
		list = list->next_entry;
		i++;
	}
	return (i);
}

int	copy_array_into_dir(char (*array)[128], int size, struct s_dir **list)
{
	int				i;
	struct s_dir*	index;

	i = size - 2;
	if (!(*list)->head)
		return (0);
	index = (*list)->head;
	while (index && i < size)
	{
		ft_strlcpy(index->file, array[i], ft_strlen(array[i]) + 1);
		i--;
		index = index->next_entry;
	}
	return (i);
}

int	s_dir_sort_alphabetically(struct s_dir* list)
{
	int		size;
	size = s_dir_get_size(list) + 1;
	char	array[size][FILE_MAXLEN];
	copy_dir_into_array(list, array, size);
	copy_array_into_dir(array, size, &list);
	if (size < 2)
		return (1);
	(void)list;
	return (size);
}
