NAME=ft_ls

SHELL = /bin/sh

CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-L$(LIBFT_DIR)
LDLIBS=-lft

LIBFT_DIR=libs/Libft/

OBJ=ft_ls.o \
	test.o

all:$(NAME)

$(NAME):$(OBJ) 

clean: 
	$(RM) $(OBJ)

fclean: clean 
	$(RM) $(NAME)

re: clean all

.PHONY:all clean fclean re
