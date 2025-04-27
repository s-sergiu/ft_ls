#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"
#include <stdlib.h>

#define T_FILE 8
#define T_FOLDER 4
#define NAME_MAX 255
#define PATH_MAX 4096
#define STDOUT "/dev/stdout"

typedef struct s_file	t_file;
typedef struct s_dir	t_dir;

struct s_file {
	struct s_file*	next_entry;
	char			name[NAME_MAX];
	unsigned char	is_directory:1;
};

struct s_dir {
	struct s_file*	files;
	int				size;
	char			name[PATH_MAX];
};

int				s_dir_is_empty(struct s_dir*);
struct s_dir*	s_dir_return_head(void);
void			s_dir_add_file_to_head(t_dir**, struct dirent*);
int				t_dir_free_memory(t_dir* dir);
int				s_dir_is_sorted(struct s_dir*);
int				s_dir_sort_alphabetically(struct s_dir*);
int				s_dir_push(t_dir**, const char*);
int				s_dir_pop(struct s_dir**);
void			s_dir_print_list(struct s_dir *);
t_file*			t_file_new(const char *);
unsigned int	s_dir_get_size(struct s_dir*);
void			s_dir_print_directory(t_dir*, void (*f)(void*));
int				is_output_a_terminal();
void			execute(char**);
t_dir*			scan_directory(DIR*);
void			print_element(void*);
void			print_debug_info(void);

#endif
