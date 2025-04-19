#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"

#define T_FILE 8
#define T_FOLDER 4
#define STDOUT "/dev/stdout"

void			list_directory(char**);
struct dirent*	read_directory(DIR *dir);
void			list_item(struct dirent *dir);

#endif
