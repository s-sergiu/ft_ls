# binary name
NAME=ft_ls

# overwrite env vars
SHELL = /bin/sh

# flags
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-L$(SUBDIRS)
LDLIBS=-lft

# libraries
SUBDIRS= libs/Libft

# object files
OBJ=ft_ls.o \

# rules
all:$(NAME)

$(NAME): $(OBJ)

subdirs : $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $(SUBDIRS)

clean: 
	$(RM) $(OBJ)


fclean: clean 
	$(RM) $(NAME)

re: clean all

# special built-in targets
.PHONY: all clean fclean re subdirs $(SUBDIRS)
