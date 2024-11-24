# binary name
NAME=ft_ls

# variables
SHELL=/bin/sh
VPATH=libs/Libft:src

# flags
CFLAGS=-Wall -Werror -Wextra -Ilibs/Libft/include

# libraries
SUBDIRS=libs/Libft

# object files
OBJ=ft_ls.o \

# rules
all:$(NAME) 

$(NAME): $(OBJ) -lft 

subdirs: $(SUBDIRS)

$(SUBDIRS): 
	@echo "Building $(SUBDIRS)..."
	@$(MAKE) -s -C $@

clean: 
	$(RM) $(OBJ)
	@$(MAKE) clean -s -C $(SUBDIRS)

fclean: clean 
	$(RM) $(NAME)
	@$(MAKE) fclean -s -C $(SUBDIRS)

re: clean all

# special built-in targets
.PHONY: all clean fclean re subdirs $(SUBDIRS)
