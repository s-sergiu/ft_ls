#include "ft_ls.h"

void read_args(char **argv) {
	int i = 1;

	print_directory(argv[i]);
	while(argv[i] != NULL)
		ft_printf("arg: %s\n", argv[i++]);
}

char *get_pwd(char **envp) {
	int i = 0;

	while (envp[i] != NULL) {
		if (!ft_strncmp(envp[i], "PWD", 3))
			return envp[i] + 4;
		i++;
	}
	return (NULL);
}

void print_directory(char *arg) {
	DIR *dir;
	struct dirent *dir_stream;

	dir = opendir(arg);
	if (errno == EACCES) {
		ft_printf("access denied\n");
		exit(EXIT_FAILURE);
	}
	dir_stream = readdir(dir);

	while(dir_stream != NULL) {
		ft_printf("%s \t", dir_stream->d_name);
		dir_stream = readdir(dir);
	}
	ft_printf("\n");
}