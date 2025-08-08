
#include "ft_ls.h"

int		main(int argc, char **argv, char **envp) 
{
	t_data*	data;

	data = init_data(argc, argv);
	(void)envp;
	data->exit_status = handle_args(data);
	if (data->valid_dirs > 0)
		execute((const char**)argv);
	return(data->exit_status);
}
