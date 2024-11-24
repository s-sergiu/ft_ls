# binary name
NAME=ft_ls

# overwrite env vars
SHELL = /bin/sh

# flags
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-L$(LIBFT_DIR)
LDLIBS=-lft

# libft
LIBFT_DIR=libs/Libft/
LIBFT=$(LIBFT_DIR)libft.a

# object files
OBJ=ft_ls.o \

# rules
all:$(NAME)

$(NAME):$(OBJ) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean: 
	$(RM) $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)


fclean: clean 
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: clean all

# special built-in targets
.PHONY:all clean fclean re
