#include "ft_ls.h"

void parse_args(char **argv) {
	int	i = 1;

	print_directory(argv[1]);
	while(argv[i] != NULL)
		i++;
}

char *get_pwd(char **envp) {
	int	i = 0;

	while (envp[i] != NULL) {
		if (!ft_strncmp(envp[i], "PWD", 3))
			return envp[i] + 4;
		i++;
	}
	return (NULL);
}

struct dirent *get_directory_stream(DIR **dir, char *arg) {
	if (!*dir)
		*dir = opendir(arg);
	if (errno) 
		print_error_and_exit(errno, arg);
	return (readdir(*dir));
}

void print_directory(char *arg) {
	struct dirent	*dir_stream = NULL;
	DIR				*dir = NULL;
		
	dir_stream = get_directory_stream(&dir, arg);
	while(dir_stream != NULL) {
		if (ft_strncmp(dir_stream->d_name, ".", 1)) {
			ft_printf("%s  ", dir_stream->d_name);
		}
		dir_stream = get_directory_stream(&dir, arg);
	}
	if (closedir(dir) != 0)
		print_error_and_exit(errno, arg);
	ft_printf("\n");
}
