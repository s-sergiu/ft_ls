#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"

#define TYPE_FILE 8
#define TYPE_FOLDER 4

void	list_directory(char**);

#endif
