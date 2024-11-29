#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

struct s_file { 
	char			name[255];
	struct s_file	*next;
};

struct s_folder { 
	char			name[255];
	struct s_folder	*next;
};

struct s_dir {
	struct s_file	*files;
	struct s_folder	*start;
	struct s_folder	*end;
	struct s_dir	*next;
};

typedef struct s_dir	t_dir;
typedef struct s_file	t_file;
typedef struct s_folder	t_folder;

char			*get_pwd(char**);
void			print_directory(char*);
void			parse_args(char**);
void			print_error_and_exit(int, char*);
struct dirent	*get_directory_stream(DIR**, char*);

#endif
