#include <unistd.h>
#include "libft.h"

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;
	int length = ft_strlen("test");
	write(1, "Success\n", 8);
	ft_printf("length %d\n", length);

	return (0);
}
