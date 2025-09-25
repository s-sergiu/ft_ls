
#include "ft_ls.h"

t_data*	init_data(int argc, char** argv, char** envp) {
	t_data*	data;
	int		index;
	int		i;

	index = 0;
	i = 0;
	while (ft_strncmp(envp[i], "PWD", 3))
		i++;
	data = (t_data *)malloc(sizeof(t_data));
	data->pwd = envp[i];
	data->argc = argc;
	data->argv = (char **)malloc(sizeof(char *) * argc);
	while (argv[index])
	{
		data->argv[index] = ft_strdup(argv[index]);
		index++;
	}
	data->exit_status = EXIT_SUCCESS;
	data->valid_dirs = 0;
	data->dirs = NULL;

	return (data);
}

void	destroy_data(t_data* data) 
{
	int	index;

	index = 0;
	while(index < data->argc)
	{
		free(data->argv[index]);
		data->argv[index] = NULL;
		index++;
	}
	free(data->argv);
	ft_lstclear(&data->dirs, free);
	free(data->dirs);
	data->argv = NULL;
	free(data);
	data = NULL;
}
