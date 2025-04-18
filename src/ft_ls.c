#include "ft_ls.h"

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;
	list_directory(*argv);
	return (EXIT_SUCCESS);
}
