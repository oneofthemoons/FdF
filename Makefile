NAME = fdf

SRC = main.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -L ./minilibx/ -lmlx -L ./libft/ -lft -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)

$(OBJ): $(SRC)
	gcc -Wall -Wextra -Werror -I ./minilibx/ -c $(SRC)

clean:
	rm -f $(OBJ) --no-print-directory

fclean: clean
	rm -f fdf --no-print-directory

re: fclean all