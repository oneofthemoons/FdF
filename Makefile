NAME = fdf

SRC = main.c error.c map_control.c validate.c positions.c free.c support.c colors.c drawing.c images.c interface.c rotate.c validate_bad.c validate_service.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	gcc -L ./minilibx/ -lmlx -L ./libft/ -lft -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)

$(OBJ): $(SRC)
	gcc -Wall -Wextra -Werror -I ./libft/ -I ./minilibx/ -c $(SRC)

clean:
	rm -f $(OBJ) --no-print-directory
	rm -f libft/*.o

fclean: clean
	rm -f libft/libft.a
	rm -f fdf --no-print-directory

re: fclean all