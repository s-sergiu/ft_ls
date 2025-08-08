# binary name
NAME=	ft_ls
CHECK=	runtests

# variables
SHELL=	/bin/sh
VPATH=	libs/Libft:src:src/tools:src/tools/dir_tools:\
		src/tools/error_handling:tests

# flags
CFLAGS=		-Wall -Werror -Wextra -Ilibs/Libft/include -Iinclude #-Wpadded
CPPFLAGS=	-Ilibs/Libft/include -Iinclude -I$(HOME)/.brew/include

# libraries
SUBDIRS=	libs/Libft
LIBFT=		$(SUBDIRS)/libft.a

# object files
OBJ=	$(NAME).o \
		utils.o \
		struct.o \
		errors.o \
		parser.o \

TEST_OBJ=	main.o \
			utils.o \
			struct.o \
			errors.o \
			parser.o \

# rules
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) -lft

test: $(CHECK) $(NAME)
	@./$(CHECK)

$(CHECK): $(TEST_OBJ) -lgtest -lft
	$(CXX) $^ -o $@ 

$(LIBFT):
ifeq ($(shell git submodule status | awk '{print $1}' | head -c 1), -)
	git submodule update --init
endif
	@echo "Building $(SUBDIRS)..."
	@$(MAKE) -s -C $(SUBDIRS)

clean: 
	$(RM) $(OBJ) $(TEST_OBJ)
	@$(MAKE) clean -s -C $(SUBDIRS)

fclean: clean 
	$(RM) $(NAME) $(CHECK)
	@$(MAKE) fclean -s -C $(SUBDIRS)

re: clean all

# special built-in targets
.PHONY: all check clean fclean re subdirs $(SUBDIRS)
