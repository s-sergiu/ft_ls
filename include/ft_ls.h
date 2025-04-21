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
	int				size;
	struct s_dir	*head;
	struct s_dir	*next_entry;
};

unsigned char	is_empty(struct s_dir *node);
struct s_dir*	get_directory_list(void);
int				s_dir_push(struct s_dir**, const char *name);
int				s_dir_pop(struct s_dir**);
struct s_dir*	s_dir_new(const char*);
void			list_dirs(void (*f)(void*));
void			execute(char**);
struct dirent*	scan_dir(DIR*);
void			add_file_to_list(struct dirent*);
void			print_item(void*);

#endif
