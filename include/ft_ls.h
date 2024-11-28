#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

char	*get_pwd(char**);
void	print_directory(char**, char*);
void	parse_args(char**);
void	print_error_and_exit(int, char**, char*);

#endif
