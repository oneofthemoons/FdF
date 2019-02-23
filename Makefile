NAME = fdf

SRC = main.c error.c map_control.c validate.c positions.c free.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -L ./minilibx/ -lmlx -L ./libft/ -lft -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)

$(OBJ): $(SRC)
	gcc -Wall -Wextra -Werror -I ./libft/ -I ./minilibx/ -c $(SRC)

clean:
	rm -f $(OBJ) --no-print-directory

fclean: clean
	rm -f fdf --no-print-directory

re: fclean all