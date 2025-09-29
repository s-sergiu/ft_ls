
#include "ft_ls.h"
//#include <locale.h>

int		main(int argc, char **argv, char **envp) 
{
	t_data*	data;
	int		exit_status;
	int		i;

	i = 0;

	data = init_data(argc, argv, envp);
	handle_args(data);
	parse_path_list(&data);
	if (data->valid_dirs > 0)
	{
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
	}
	else
		execute(data, 0);
	exit_status = data->exit_status;
	destroy_data(data);

	return(exit_status);
}
