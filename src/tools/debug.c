
#include "ft_ls.h"

void	print_debug_info(void)
{
	char		buf[13];

	readlink("/proc/self/fd/1", buf, 13);
	ft_printf("\n----------DEBUG-----------------\n");
	ft_printf("Output is: %s\n", buf);
	ft_printf("----------------------------------\n");
}

void	print_data_info(t_data* data)
{
	int		i;
	t_list*	temp;

	i = 0;
	temp = data->dirs;

	ft_printf("\n----------Variables-------------------\n");
	ft_printf("exit_status is: %d\n", data->exit_status);
	ft_printf("valid dirs is: %s\n", data->valid_dirs);
	ft_printf("argc is: %d\n", data->argc);
	ft_printf("--------------------------------------\n");
	ft_printf("\n----------Argv------------------------\n");
	while (data->argv[i])
	{
		ft_printf("argv[%d] is: %s\n", i, data->argv[i]);
		i++;
	}
	ft_printf("--------------------------------------\n");
	ft_printf("\n----------Dirs------------------------\n");
	i = 0;
	while (temp)
	{
		ft_printf("dirs[%d] is: %s\n", i, temp->content);
		temp = temp->next;
		i++;
	}
	ft_printf("--------------------------------------\n");
}
