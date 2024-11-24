#include <unistd.h>
#include "libft.h"

char *get_pwd(char **envp) {
	int i = 0;

	while (envp[++i] != NULL)
		if (!ft_strncmp(envp[i], "PWD", 3))
			return envp[i] + 4;
	return (NULL);
}

int main(int argc, char **argv, char **envp) {
	char *pwd;

	if (argc > 1)
		ft_printf("args: %s\n", *argv);

	pwd = get_pwd(envp);
	ft_printf("%s\n", pwd);

	return (0);
}
