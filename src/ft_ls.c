
#include "ft_ls.h"

int	main(int argc, char **argv, char **envp) 
{
	(void)envp;
	(void)argc;
	handle_args(argv);
	execute(argv);
	return(EXIT_SUCCESS);
}
