#include "ft_ls.h"

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;
	if (argc > 1)
		ft_printf("parse args\n");
	ft_printf("extract PWD\n");
	ft_printf("execute\n");
	return (EXIT_SUCCESS);
}
