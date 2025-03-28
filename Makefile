NAME	= minirt
CC		= cc
FLAGS	= -Wall -Wextra -Werror
FLAGS	+= -fsanitize=thread -g
SRC_M   = src/main.c
SRC_B   = src/main_bonus.c
SRCS	= src/parser/check_element.c \
		  src/parser/check_range.c \
		  src/parser/free.c \
		  src/parser/ft_atof.c \
		  src/parser/init.c\
		  src/parser/make_env_data.c \
		  src/parser/make_lit_data.c \
		  src/parser/make_obj_data.c \
		  src/parser/parser.c \
		  src/parser/print_function.c \
		  src/parser/setter_getter.c \
		  src/parser/utils.c 

OBJ_M   = $(SRC_M:.c=.o)
OBJ_B   = $(SRC_B:.c=.o)
OBJS	= $(SRCS:.c=.o)
HEADER	= ./includes
LIBFT	= ./src/libft/libft.a

%.o: %.c
	$(CC) $(FLAGS) -I$(HEADER) -c $< -o $@

$(NAME): $(OBJ_M) $(OBJS)
	make -C ./src/libft
	$(CC) $(FLAGS) $(OBJ_M) $(OBJS) $(LIBFT) -lm -o $(NAME)

all: $(NAME)

bonus: $(OBJ_B) $(OBJS)
	make -C ./src/libft
	$(CC) $(FLAGS) $(OBJ_B) $(OBJS) $(LIBFT) -lm -o $(NAME)

clean:
	make fclean -C ./src/libft
	rm -f $(OBJ_M) $(OBJ_B) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
