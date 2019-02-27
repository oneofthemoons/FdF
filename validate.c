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

void	ft_bad_map(int fd, char *c_map)
{
	free(c_map);
	close(fd);
	ft_print_error("error: bad map\n");
}

int		ft_width_in_num_rep(char *buff, int fd, int *i, int len)
{
	int	width;

	width = 0;
	while (buff[*i] != '\n' && buff[*i] && *i < len)
	{
		if (buff[*i] == '-')
		{
			if ((*i > 0 && buff[*i - 1] != ' ' && buff[*i - 1] != '\n') ||
				buff[*i + 1] < '0' || buff[*i + 1] > '9')
				ft_bad_map(fd, buff);
			++(*i);
		}
		else if (buff[*i] >= '0' && buff[*i] <= '9' && *i < len)
		{
			++width;
			while (buff[*i] >= '0' && buff[*i] <= '9' && *i < len)
				++(*i);
		}
		else if (buff[*i] != ' ' && buff[*i] != '\n' && buff[*i])
			ft_bad_map(fd, buff);
		while (buff[*i] == ' ' && *i < len)
			++(*i);
	}
	return (width);
}

int		ft_map_check(char *c_map, int fd)
{
	int		width;
	int		i;
	int		len;

	width = -1;
	len = ft_strlen(c_map);
	i = -1;
	while (++i < len)
		if (width == -1)
			width = ft_width_in_num_rep(c_map, fd, &i, len);
		else if (width != ft_width_in_num_rep(c_map, fd, &i, len))
			ft_bad_map(fd, c_map);
	close(fd);
	return (width);
}

char	*ft_get_char_map(int argc, char **argv, t_fdf *fdf)
{
	int		fd;
	char	*c_map;
	char	*t;
	char	buff[BUFF_FDF + 1];
	int		len;

	if (argc != 2)
		ft_print_error("input error: bad argument count\n");
	fd = open(argv[1], O_RDONLY);
	if (read(fd, buff, 0) == -1)
		ft_print_error("input error: file descriptor was closed\n");
	c_map = ft_strdup("");
	while ((len = read(fd, buff, BUFF_FDF)))
	{
		buff[len] = '\0';
		t = c_map;
		c_map = ft_strjoin(c_map, buff);
		free(t);
	}
	fdf->s_map.width = ft_map_check(c_map, fd);
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