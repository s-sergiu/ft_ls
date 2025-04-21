# binary name
NAME=	ft_ls
CHECK=	runtests

# variables
SHELL=	/bin/sh
VPATH=	libs/Libft:src:src/tools:src/tools/dir_tools:\
		src/tools/error_handling:tests

# flags
CFLAGS=	-Wall -Werror -Wextra -Ilibs/Libft/include -Iinclude
CPPFLAGS= -Ilibs/Libft/include -Iinclude -I$(HOME)/.brew/include
VFLAGS= --leak-check=full

# libraries
SUBDIRS=	libs/Libft

# object files
OBJ=	$(NAME).o \
		utils.o \
		errors.o \
		dir_stack.o

TEST_OBJ=	main.o \
			utils.o \
			errors.o \
			dir_stack.o

# rules
all:$(NAME) 

$(NAME): $(OBJ) -lft

test: $(CHECK) $(NAME)
	@./$(CHECK)

$(CHECK): $(TEST_OBJ) -lgtest -lft
	$(CXX) $^ -o $@ 

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
