#include "ft_ls.h"

struct s_dir	*directory = NULL;

void	list_dirs(struct s_dir* dir, void (*f)(void *))
{
	struct s_dir	*curr;

	curr = dir;
	while (curr)
	{
		f(curr->file);
		curr = curr->next;
	}
}

void	dir_add_front(struct s_dir** lst, struct s_dir* new) {
	new->next = *lst;
	*lst = new;
}

struct s_dir*	dir_new(char *arg) 
{
	struct s_dir	*new;
	new = (struct s_dir*)malloc(sizeof(struct s_dir));
	if (!arg)
		return (NULL);
	if (!new)
		return (NULL);
	ft_strlcat(new->file, arg, ft_strlen(arg - 1));
	new->next = NULL;
	return (new);
}

void	add_file_to_list(struct dirent *dir)
{
	if (dir->d_name[0] == '.')
		return ;
	dir_add_front(&directory, dir_new(dir->d_name));
}

struct dirent*	scan_dir(DIR *dir)
{
	struct dirent	*dir_struct;

	dir_struct = readdir(dir);
	if (!dir_struct)
		return (NULL);
	add_file_to_list(dir_struct);
	return 	(scan_dir(dir));
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
	DIR*			dir;
	struct stat		file_stats;

	stat(STDOUT, &file_stats);
	dir = opendir(args[1]);
	if (!dir)
		return ;
	if (*args[1])
		scan_dir(dir);
	list_dirs(directory, print_item);
	if (file_stats.st_rdev != 0)
		ft_printf("\n");
}
