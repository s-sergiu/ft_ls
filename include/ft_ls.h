#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"
#include <stdlib.h>

#define T_FILE 8
#define T_FOLDER 4
#define NAME_MAXLEN 257
#define PATH_MAX 4096
#define STDOUT "/dev/stdout"
#define STRLEN 0
#define ILLEGAL_FLAG 10
#define FLAGS 1
#define FLAG_HIDDEN 0x1
#define FLAG_VISIBLE 0x2

int				is_output_a_terminal();
void			execute(char**);
void			scan_directory(char[][NAME_MAXLEN], char*);
void			print_debug_info(void);
int				get_number_of_files(char*);
int				handle_args(char**);
void			check_illegal_flag(char*);
void			send_error(int, char);

#endif
