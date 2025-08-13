
#include "ft_ls.h"

int		main(int argc, char **argv, char **envp) 
{
	t_data*	data;

	data = init_data(argc, argv);
	(void)envp;
	handle_args(data);
	print_data_info(data);
	if (data->valid_dirs > 0)
		execute((const char**)argv);
	//destroy_data(data);
	return(data->exit_status);
}
