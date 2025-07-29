#include "ft_ls.h"

int	main(int argc, char **argv, char **envp) 
{
	(void)envp;
	(void)argc;
	(void)argv;
	execute(argv, envp[5]);
	return(EXIT_SUCCESS);
}
