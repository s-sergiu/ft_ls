#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"
#include <stdlib.h>

#define T_FILE 8
#define T_FOLDER 4
#define STR_MAXLEN 128
#define STDOUT "/dev/stdout"

struct s_dir {
	struct s_dir*	head;
	struct s_dir*	next_entry;
	int				size;
	char			file[STR_MAXLEN];
};

int				s_dir_is_empty(struct s_dir*);
struct s_dir*	s_dir_return_head(void);
void			s_dir_add_file_to_head(struct dirent*);
int				s_dir_free_memory(struct s_dir*);
int				s_dir_is_sorted(struct s_dir*);
int				s_dir_sort_alphabetically(struct s_dir*);
int				s_dir_push(struct s_dir**, const char*);
int				s_dir_pop(struct s_dir**);
void			s_dir_print_list(struct s_dir *);
struct s_dir*	s_dir_new(const char*);
unsigned int	s_dir_get_size(struct s_dir*);
void			s_dir_print_directory(void (*f)(void*));
int				is_output_a_terminal();
void			execute(char**);
struct dirent*	scan_directory(DIR*);
void			print_element(void*);
void			print_debug_info(void);

#endif
