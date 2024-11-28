# binary name
NAME=ft_ls
CHECK=runtests

# variables
SHELL=/bin/sh
VPATH=libs/Libft:src:tests

# flags
CFLAGS=-Wall -Werror -Wextra -Ilibs/Libft/include -Iinclude

# libraries
SUBDIRS=libs/Libft

# object files
OBJ=$(NAME).o \
	utils.o

TEST_OBJ=maintest.o \
		 utils.o

# rules
all:$(NAME) 

$(NAME): $(OBJ) -lft

check: $(CHECK)
	-@./$(CHECK) || true

$(CHECK): $(TEST_OBJ) -lcheck -lft
	$(CC) $^ -o $@ 

subdirs: $(SUBDIRS)

$(SUBDIRS): 
	@echo "Building $(SUBDIRS)..."
	@$(MAKE) -s -C $@

clean: 
	$(RM) $(OBJ) $(TEST_OBJ)
	@$(MAKE) clean -s -C $(SUBDIRS)

fclean: clean 
	$(RM) $(NAME) $(CHECK)
	@$(MAKE) fclean -s -C $(SUBDIRS)

re: clean all

# special built-in targets
.PHONY: all check clean fclean re subdirs $(SUBDIRS)
