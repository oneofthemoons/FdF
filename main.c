#include "fdf.h"
#include "libft.h"

void	ft_print_error(char* strerr)
{
	printf("%s", strerr); // deb to ft_putstr
	exit(EXIT_FAILURE);
}

int ft_deal_key(int key, void *mlx)
{
	if (key == 53)
		exit(0);
	if (key == 1 && ((t_fdf*)mlx)->cur_pos.y < WIN_HEIGHT)
		((t_fdf*)mlx)->cur_pos.y += PIXEL_RANGE;
	else if (key == 2 && ((t_fdf*)mlx)->cur_pos.x < WIN_WIDTH)
		((t_fdf*)mlx)->cur_pos.x += PIXEL_RANGE;
	else if (key == 13 && ((t_fdf*)mlx)->cur_pos.y > 0)
		((t_fdf*)mlx)->cur_pos.y -= PIXEL_RANGE;
	else if (key == 0 && ((t_fdf*)mlx)->cur_pos.x > 0)
		((t_fdf*)mlx)->cur_pos.x -= PIXEL_RANGE;
	mlx_pixel_put(((t_fdf*)mlx)->mlx_ptr, ((t_fdf*)mlx)->win_ptr, ((t_fdf*)mlx)->cur_pos.x, ((t_fdf*)mlx)->cur_pos.y, 0xFFFFFF);
	return (0);
}

void	ft_reset_pos(t_pos *pos)
{
	pos->x = 0;
	pos->y = 0;
	pos->z = 0;
}

int		ft_width_in_num_rep(char *buff, int fd, int *i, int len)
{
	int	width;

	width = 0;
	while (buff[*i] != '\n' && buff[*i] && *i < len)
		if (buff[*i] >= '0' && buff[*i] <= '9')
		{
			++width;
			while (buff[*i] >= '0' && buff[*i] <= '9' && *i < len)
				++(*i);
		}
		else if (buff[*i] == ' ')
			while (buff[*i] == ' ' && *i < len)
				++(*i);
		else if (buff[*i] != '\n' && buff[*i])
		{
			close(fd);
			ft_print_error("error: bad map\n");
		}
	if (buff[len - 1] != '\n')
	{
		close(fd);
		ft_print_error("error: bad map\n");
	}
	return (width);
}

int		ft_map_check(int argc, char **argv)
{
	int		fd;
	char	buff[BUFF_FDF];
	int		width;
	int		i;
	int		len;

	if (argc != 2)
		ft_print_error("input error: bad argument count\n");
	fd = open(argv[1], O_RDONLY);
	if (read(fd, buff, 0) == -1)
		ft_print_error("input error: file descriptor was closed\n");
	width = -1;
	while ((len = read(fd, buff, BUFF_FDF)))
	{
		i = -1;
		while (++i < len)
			if (width == -1)
				width = ft_width_in_num_rep(buff, fd, &i, len);
			else if (width != ft_width_in_num_rep(buff, fd, &i, len))
			{
				close(fd);
				ft_print_error("error: bad map\n");
			}
	}
	close(fd);
	return (width);
}

char	*ft_get_char_map(char *filename)
{
	int		fd;
	char	*c_map;
	char	*t;
	char	buff[BUFF_FDF + 1];
	int		len;

	c_map = ft_strdup("");
	fd = open(filename, O_RDONLY);
	while ((len = read(fd, buff, BUFF_FDF)))
	{
		buff[len] = '\0';
		t = c_map;
		c_map = ft_strjoin(c_map, buff);
		free(t);
	}
	return (c_map);
	close(fd);
}

int		ft_get_height(char *map)
{
	int	height;

	height = 0;
	while (*map)
		if (*(map++) == '\n')
			++height;
	return (height);
}

void	ft_free_string_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_set_pos(t_pos *pos, int x, int y, int z)
{
	pos->x = x;
	pos->y = y;
	pos->z = z;
}

void	ft_include_int_map(char* c_map, t_map *map)
{
	char	**s_map;
	char	**t;
	int		i;
	int		j;

	s_map = ft_strsplit(c_map, '\n');
	map->height = ft_get_height(c_map);
	map->points = (t_pos**)malloc(sizeof(t_pos*) * map->height);
	free(c_map);
	i = -1;
	while (++i < map->height)
	{
		t = ft_strsplit(s_map[i], ' ');
		map->points[i] = (t_pos*)malloc(sizeof(t_pos) * map->width);
		j = -1;
		while (++j < map->width)
			ft_set_pos(&(map->points[i][j]), j, i, ft_atoi(t[j]));
		ft_free_string_arr(t);
	}
	ft_free_string_arr(s_map);
}

void	ft_create_map(t_map *map, int argc, char **argv)
{
	map->width = ft_map_check(argc, argv);
	ft_include_int_map(ft_get_char_map(argv[1]), map);
}

// void	ft_print_map_to_debug(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < map->height)
// 	{
// 		j = -1;
// 		while (++j < map->width)
// 		{
// 			ft_putnbr(map->points[i][j].z);
// 			ft_putchar(' ');
// 		}
// 		ft_putchar('\n');
// 	}
// }

int main(int argc, char **argv)
{
	t_fdf	mlx;
	t_map	s_map;
	//t_map	c_map;

	ft_create_map(&s_map, argc, argv);
	// ft_print_map_to_debug(&s_map);
	ft_reset_pos(&(mlx.cur_pos));
    mlx.mlx_ptr = mlx_init();
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "PUPA_WIN_A");
    mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, mlx.cur_pos.x, mlx.cur_pos.y, 0xFFFFFF);
    mlx_key_hook(mlx.win_ptr, ft_deal_key, (void*)(&mlx));
    mlx_loop(mlx.mlx_ptr);
}