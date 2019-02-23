#include "fdf.h"

int		ft_get_height(char *map)
{
	int	height;

	height = 0;
	while (*map)
		if (*(map++) == '\n')
			++height;
	return (height);
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