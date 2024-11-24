#include <unistd.h>
#include <stdio.h>
#include "../libs/Libft/include/libft.h"

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;
	int length = ft_strlen("test");
	write(1, "Success\n", 8);
	printf("length %d\n", length);

	return (0);
}
