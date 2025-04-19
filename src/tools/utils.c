#include "ft_ls.h"

void	list_item(struct dirent *dir)
{
	struct stat		file_stats;

	stat(STDOUT, &file_stats);
	if (dir->d_name[0] == '.')
		return ;
	ft_printf("%s", dir->d_name);
	if (file_stats.st_rdev != 0)
		ft_printf("  ");
	else
		ft_printf("\n");
}

struct dirent*	read_directory(DIR *dir)
{
	struct dirent	*dir_struct;

	dir_struct = readdir(dir);
	if (!dir_struct)
		return (NULL);
	list_item(dir_struct);
	return 	(read_directory(dir));
}

void	list_directory(char **args)
{
	struct stat		file_stats;
	DIR*			dir;

	stat(STDOUT, &file_stats);
	dir = opendir(args[1]);
	if (!dir)
		return ;
	if (*args[1])
		read_directory(dir);
	if (file_stats.st_rdev != 0)
		ft_printf("\n");
}
