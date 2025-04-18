#include "ft_ls.h"

int	main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;
	if(argc > 1)
		list_directory(*argv);
	else
		list_directory(*argv);
	return(EXIT_SUCCESS);
}
