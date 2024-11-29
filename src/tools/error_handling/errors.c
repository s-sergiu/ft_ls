#include "ft_ls.h"

void print_error_and_exit(int errnum, char *arg) {

	if (errnum == EACCES) {
		ft_printf("ft_ls : cannot open directory '%s': %s\n", 
					arg, strerror(errno));
		exit(EXIT_FAILURE);
	} else if (errnum == ENOENT) {
		ft_printf("ft_ls : cannot access '%s': %s\n", arg, strerror(errno));
		exit(EXIT_FAILURE);
	} else if (errnum == ENOMEM) {
		ft_printf("ft_ls: cannot access '%s': %s\n", arg, strerror(errno));
		exit(EXIT_FAILURE);
	} else if (errnum == EBADF) {
		ft_printf("ft_ls : Internal error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
