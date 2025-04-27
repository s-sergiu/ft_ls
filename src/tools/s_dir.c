
#include "ft_ls.h"

int	s_dir_is_sorted(t_dir* dir)
{
	t_file*	index;
	char*	str1;
	char*	str2;

	if (!dir || !dir->files)
		return (1);
	index = dir->files;
	while (index->next_entry)
	{
		str1 = index->name;
		str2 = index->next_entry->name;
		if (ft_strncmp(str1, str2, ft_strlen(str1)) < 0)
			return (0);
		index = index->next_entry;
	}
	return (1);
}

void	print_dir(t_dir* dir)
{
	int		i;
	t_file*	index;

	i = 0;
	index = dir->files;
	while(index)
	{
		ft_printf("file[%d]: %s\n", i, index->name);
		i++;
		index = index->next_entry;
	}
}

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
	t_file*	file;

	if (!dir || !(*dir) || (*dir)->size == 0)
		return -1;
	file = (*dir)->files;
	(*dir)->files = file->next_entry;
	(*dir)->size--;
	free(file);
	return (1);
}

int	s_dir_is_empty(t_dir* dir)
{
	if (dir->size == 0)
		return (1);
	return (0);
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

