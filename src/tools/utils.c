#include "ft_ls.h"

void	list_directory(char **args) {
	struct stat buf;
	fstat(1, &buf);

	if (*args[1]) {
		struct dirent *dir_struct;
		DIR * dir;

		dir = opendir(args[1]);
		dir_struct = readdir(dir);
		while (dir_struct)
		{
			if (dir_struct->d_type == TYPE_FILE &&
				dir_struct->d_name[0] != '.')
			{
				ft_printf("%s", dir_struct->d_name);
				if (buf.st_rdev != 0)
					ft_printf("  ");
				else
					ft_printf("\n");
			}
			if (dir_struct->d_type == TYPE_FOLDER &&
				dir_struct->d_name[0] != '.')
			{
				ft_printf("%s", dir_struct->d_name);
				if (buf.st_rdev != 0)
					ft_printf("  ");
				else
					ft_printf("\n");
			}
			dir_struct = readdir(dir);
		}
		if (buf.st_rdev != 0)
			ft_printf("\n");
	}
}
