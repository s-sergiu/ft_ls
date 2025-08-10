
#include "ft_ls.h"

t_data*	init_data(int argc, char** argv) {
	t_data*	data;
	int		index;

	index = 0;
	data = (t_data *)malloc(sizeof(t_data));
	data->argc = argc;
	data->argv = (char **)malloc(sizeof(char *) * argc);
	while (argv[index])
	{
		data->argv[index] = ft_strdup(argv[index]);
		index++;
	}
	data->argv[index] = NULL;
	data->exit_status = EXIT_SUCCESS;
	data->valid_dirs = 0;
	data->dirs = NULL;

	return (data);
}

void	destroy_data(t_data* data) 
{
	int	index;

	index = 0;
	while(data->argv[index])
	{
		free(data->argv[index]);
		data->argv[index] = NULL;
		index++;
	}
	free(data->argv);
	data->argv = NULL;
}
