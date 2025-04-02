NAME	= miniRT
NAME_B  = miniRT_bonus
CC		= cc
FLAGS	= -Wall -Wextra -Werror
FLAGS	+= -fsanitize=thread -g
SRCS_M  = src/main.c
SRCS_B  = src/main_bonus.c
SRCS_P	= src/parser/check_element.c \
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
SRCS_C	= src/calc/dot_cross.c \
		  src/calc/multi_divid_vector.c \
		  src/calc/plus_minus_vector.c \
		  src/calc/normalize.c \
		  src/calc/test.c

OBJS_M  = $(SRCS_M:.c=.o)
OBJS_B  = $(SRCS_B:.c=.o)
OBJS_P	= $(SRCS_P:.c=.o)
OBJS_C	= $(SRCS_C:.c=.o)
HEADER	= ./includes
LIBFT	= ./src/libft/libft.a

%.o: %.c
	$(CC) $(FLAGS) -I$(HEADER) -c $< -o $@

$(NAME): $(OBJS_M) $(OBJS_P) $(OBJS_C)
	make -C ./src/libft
	$(CC) $(FLAGS) $(OBJS_M) $(OBJS_P) $(OBJS_C) $(LIBFT) -lm -o $(NAME)

all: $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJS_B) $(OBJS_P) $(OBJS_C)
	make -C ./src/libft
	$(CC) $(FLAGS) $(OBJS_B) $(OBJS_P) $(OBJS_C) $(LIBFT) -lm -o $(NAME_B)

clean:
	make fclean -C ./src/libft
	rm -f $(OBJS_M) $(OBJS_B) $(OBJS_P) $(OBJS_C)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re bonus
