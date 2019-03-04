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
	// ft_central(fdf);
}

void	ft_create_maps(t_fdf *fdf, int argc, char **argv)
{
	ft_include_int_map(ft_get_char_map(argc, argv, fdf), &(fdf->s_map));
	ft_create_current_map(&(fdf->c_map), &(fdf->s_map));
}

void	ft_recalculate_points(t_fdf *fdf, int action)
{
	int	i;
	int	j;

	if (fdf->params.cell_range < 4)
		fdf->params.cell_range = 4;
	if (fdf->params.cell_range > WIN_WIDTH / 2)
		fdf->params.cell_range = WIN_WIDTH / 2;
	i = -1;
	while (++i < fdf->s_map.height)
	{
		j = -1;
		while (++j < fdf->s_map.width)
			fdf->s_map.points[i][j].z /= fdf->params.cell_range;
	}
	if (action == REDUCE)
		fdf->params.cell_range = (fdf->params.cell_range * 3) / 4;
	else if (action == INCREASE)
		fdf->params.cell_range = (fdf->params.cell_range * 4) / 3;
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
}

void	ft_calculate_params(t_fdf *fdf)
{
	int	i;
	int	j;

	fdf->params.cell_range = (WIN_WIDTH - fdf->params.left * 2) / fdf->s_map.width;
	fdf->params.left = -(fdf->s_map.width * fdf->params.cell_range) / 2;
	fdf->params.top = -(fdf->s_map.height * fdf->params.cell_range) / 2;
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
