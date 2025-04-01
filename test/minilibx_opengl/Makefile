#
#

NAME=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11 -w

all: $(NAME)

# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Isrc -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -Lsrc -lsrc -framework OpenGL -framework AppKit -o $(NAME)

$(NAME):	$(OBJ)
	ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(NAME) $(OBJ) *~
	rm -f mlx_app

fclean: clean
	rm -f $(NAME)

re: clean all fclean
