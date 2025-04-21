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
	struct s_dir	*head;
	struct s_dir	*next;
};

struct s_dir*	get_directory_list(void);
void			s_dir_add_front(struct s_dir*);
struct s_dir*	s_dir_new(char*);
void			list_dirs(void (*f)(void*));
void			execute(char**);
struct dirent*	scan_dir(DIR*);
void			add_file_to_list(struct dirent*);
void			print_item(void*);

#endif
