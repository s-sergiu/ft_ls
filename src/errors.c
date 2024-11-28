#include "ft_ls.h"

void print_error_and_exit(int errnum, char **argv, char *arg) {

	if (errnum == EACCES) {
		ft_printf("%s: cannot open directory '%s': %s\n",
					argv[0], arg, strerror(errno));
		exit(EXIT_FAILURE);
	} else if (errnum == ENOENT) {
		ft_printf("%s: cannot access '%s': %s\n",
					argv[0], arg, strerror(errno));
		exit(EXIT_FAILURE);
	} else if (errnum == ENOMEM) {
		ft_printf("%s: cannot access '%s': %s\n",
					argv[0], arg, strerror(errno));
		exit(EXIT_FAILURE);
	} else if (errnum == EBADF) {
		ft_printf("%s: Internal error: %s\n",
					argv[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
}
