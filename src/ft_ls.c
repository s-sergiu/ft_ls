
#include "ft_ls.h"
//#include <locale.h>

int		main(int argc, char **argv, char **envp) 
{
	t_data*	data;
	int		exit_status;
	int		st;
	int		i;
	struct stat	buffer;

	i = 0;
	(void)st;

	//setlocale(LC_COLLATE, "en_US.utf-8");

	st = stat("/home/ssergiu/repos/projects/ft_ls/Makefile", &buffer);
	ft_printf("st: %d\n", st);
	ft_printf("error %s\n", strerror(errno));
	ft_printf("st_dev %d\n", buffer.st_dev);
	ft_printf("st_ino %d\n", buffer.st_ino);
	ft_printf("st_mode %d\n", buffer.st_mode);
	ft_printf("st_nlink %d\n", buffer.st_nlink);
	ft_printf("st_uid %d\n", buffer.st_uid);
	ft_printf("st_gid %d\n", buffer.st_gid);
	ft_printf("st_rdev %d\n", buffer.st_rdev);
	ft_printf("st_size %d\n", buffer.st_size);
	ft_printf("st_blksize %d\n", buffer.st_blksize);
	ft_printf("st_blocks %d\n", buffer.st_blocks);

	ft_printf("ISFREG %d\n", S_IFREG);
	data = init_data(argc, argv, envp);
	handle_args(data);
	parse_path_list(&data);
	if (data->valid_dirs > 0)
		while (i < data->valid_dirs)
		{
			if (argc > 2)
			{
				ft_putstr_fd(data->argv[i + 1], 1);
				write(1, ":\n", 2);
			}
			execute(data, i++);
			if (is_output_a_terminal() && i < data->valid_dirs)
				write(1, "\n", 1);
		}
	exit_status = data->exit_status;
	destroy_data(data);

	return(exit_status);
}
