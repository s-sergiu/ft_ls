#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "libft.h"

char			*get_pwd(char**);
void			print_directory(char*);
void			parse_args(char**);
void			print_error_and_exit(int, char*);
struct dirent	*get_directory_stream(DIR**, char*);

#endif
