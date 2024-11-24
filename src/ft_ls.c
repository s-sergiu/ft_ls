#include <unistd.h>
#include "libft.h"

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;

	ft_printf("%s\n", envp[7]);

	return (0);
}
