
#include "ft_ls.h"

void	print_debug_info(void)
{
	char		buf[13];

	readlink("/proc/self/fd/1", buf, 13);
	ft_printf("\n----------DEBUG-----------------\n", buf);
	ft_printf("Output is: %s\n", buf);
	ft_printf("--------------------------------\n", buf);
}
