NAME	= minirt
CC		= cc
FLAGS	= -Wall -Wextra -Werror
FLAGS	+= -fsanitize=thread -g
SRCS	= src/main.c \
		  src/parser/check_element.c \
		  src/parser/check_range.c \
		  src/parser/free.c \
		  src/parser/ft_atof.c \
		  src/parser/init.c\
		  src/parser/make_env_data.c \
		  src/parser/make_obj_data.c \
		  src/parser/parser.c \
		  src/parser/print_function.c \
		  src/parser/setter_getter.c \
		  src/parser/utils.c \
		  src/ui/init_window.c \
		  src/ui/close_handler.c
OBJS	= $(SRCS:.c=.o)
HEADER	= ./includes
LIBFT	= ./src/libft/libft.a

%.o: %.c
	$(CC) $(FLAGS) -I$(HEADER) -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	@make -C ./mlx_linux
	make -C ./src/libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

all: $(NAME)

clean:
	make fclean -C ./src/libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
