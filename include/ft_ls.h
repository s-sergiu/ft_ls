#ifndef LS_HPP
#define LS_HPP

#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define T_FILE 8
#define T_FOLDER 4
#define NAME_MAXLEN 257
#define PATH_MAX 4096
#define STDOUT "/dev/stdout"
#define STRLEN 0
#define FLAGS 1
#define NAME 2
#define ILLEGAL_FLAG 10
#define ACCESS_FLAG 11
#define FLAG_HIDDEN 0x1
#define FLAG_VISIBLE 0x2

typedef struct s_flags t_flags;

struct s_flags {
	int	exit_status;
	int valid_dirs;
};

int				is_output_a_terminal();
t_flags			*init_flags(void);
void			execute(const char**);
void			scan_directory(char[][NAME_MAXLEN], const char*);
void			print_debug_info(void);
int				get_number_of_files(const char*);
int				handle_args(const char**, int);
int				is_valid_flag(const char**, int);
void			send_error(int, const char**, int, int);

#endif

/* 
 * Allowed functions:
 * write();
 * opendir();
 * readdir();
 * closedir();
 * stat();
 * lstat();
 * getpwuid();
 * getgrgid();
 * listxattr();
 * getxattr();
 * time();
 * ctime();
 * readlink();
 * malloc();
 * free();
 * perror();
 * strerror();
 * exit();
*/
