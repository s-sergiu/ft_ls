#include "ft_ls.h"

int main(int argc, char **argv, char **envp) {

	if (argc > 1)
		parse_args(argv);
	else
		print_directory(argv, get_pwd(envp));

	return (EXIT_SUCCESS);
}
