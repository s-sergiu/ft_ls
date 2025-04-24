
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

int	s_dir_sort_alphabetically(struct s_dir* list)
{
	(void)list;
	return 1;
}
