NAME	= minirt
CC		= cc
FLAGS	= -Wall -Wextra -Werror
FLAGS	+= -fsanitize=thread -g
SRCS	= src/main.c \
		  src/parser/open_file.c \
		  src/parser/error_msg.c \
		  src/parser/ft_atof.c
		#   src/parser/setter_getter.c
OBJS	= $(SRCS:.c=.o)
HEADER	= ./includes
LIBFT	= ./src/libft/libft.a

%.o: %.c
	$(CC) $(FLAGS) -I$(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	make -C ./src/libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	make fclean -C ./src/libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
