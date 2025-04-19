#include "ft_ls.h"

int	main(int argc, char **argv, char **envp) {
	(void)envp;
	(void)argc;
	list_directory(argv);
	return(EXIT_SUCCESS);
}
