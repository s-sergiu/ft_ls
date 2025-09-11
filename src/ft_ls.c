
#include "ft_ls.h"

int		main(int argc, char **argv, char **envp) 
{
	t_data*	data;
	int		exit_status;

	data = init_data(argc, argv);
	(void)envp;
	handle_args(data);
	parse_path_list(&data);
	//print_data_info(data);
	if (data->valid_dirs > 0)
		execute((const char**)argv);
	exit_status = data->exit_status;
	destroy_data(data);
	return(exit_status);
}
