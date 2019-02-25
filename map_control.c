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
	fdf->params.angle.x = 0;
	fdf->params.angle.y = 0;
	fdf->params.angle.z = 0;
}

void	ft_create_maps(t_fdf *fdf, int argc, char **argv)
{
	fdf->s_map.width = ft_map_check(argc, argv);
	ft_include_int_map(ft_get_char_map(argv[1]), &(fdf->s_map));
	ft_create_current_map(&(fdf->c_map), &(fdf->s_map));
}

void	ft_calculate_params(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->params.left = WIN_WIDTH / 6;
	fdf->params.cell_range = (WIN_WIDTH - fdf->params.left * 2) / fdf->s_map.width;
	fdf->params.top = (WIN_HEIGHT - fdf->params.cell_range * fdf->s_map.height) / 2;
	i = -1;
	while (++i < fdf->s_map.height)
	{
		j = -1;
		while (++j < fdf->s_map.width)
		{
			fdf->s_map.points[i][j].x = fdf->params.left + fdf->params.cell_range * j;
			fdf->s_map.points[i][j].y = fdf->params.top + fdf->params.cell_range * i;
			fdf->s_map.points[i][j].z *= fdf->params.cell_range;
		}
	}
	ft_reset_current_map(fdf);
}
