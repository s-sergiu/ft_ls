#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"

#define T_FILE 8
#define T_FOLDER 4
#define STDOUT "/dev/stdout"

struct s_dir {
	char			file[128];
	struct s_dir	*next;
};

void			dir_add_front(struct s_dir**, struct s_dir*);
struct s_dir*	dir_new(char*);
void			list_dirs(struct s_dir*, void (*f)(void*));
void			execute(char**);
struct dirent*	scan_dir(DIR*);
void			add_file_to_list(struct dirent*);
void			print_item(void*);

#endif
