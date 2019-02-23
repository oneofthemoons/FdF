#include "fdf.h"

void	ft_create_current_map(t_map *c_map, const t_map *s_map)
{
	int	i;

	c_map->height = s_map->height;
	c_map->width = s_map->width;
	c_map->points = (t_pos**)malloc(sizeof(t_pos**) * c_map->height);
	i = -1;
	while (++i < c_map->height)
		c_map->points[i] = (t_pos*)malloc(sizeof(t_pos) * c_map->width);
}

void	ft_reset_current_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
			ft_set_pos(&(fdf->c_map.points[i][j]), fdf->s_map.points[i][j].x,
				fdf->s_map.points[i][j].y, fdf->s_map.points[i][j].z);
	}
}

void	ft_create_maps(t_fdf *fdf, int argc, char **argv)
{
	fdf->s_map.width = ft_map_check(argc, argv);
	ft_include_int_map(ft_get_char_map(argv[1]), &(fdf->s_map));
	ft_create_current_map(&(fdf->c_map), &(fdf->s_map));
}
