#include "fdf.h"

void	ft_create_sub_map(t_map *c_map, const t_map *s_map)
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
		{
			ft_set_pos(&(fdf->c_map.points[i][j]), fdf->s_map.points[i][j].x,
				fdf->s_map.points[i][j].y, fdf->s_map.points[i][j].z);
			fdf->c_map.points[i][j].src_color = fdf->s_map.points[i][j].src_color;
		}
	}
}

void	ft_init_h_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->h_map.height)
	{
		j = -1;
		while (++j < fdf->h_map.width)
			ft_set_pos(&(fdf->h_map.points[i][j]), fdf->s_map.points[i][j].x,
				fdf->s_map.points[i][j].y, fdf->s_map.points[i][j].z);
	}
}

void	ft_create_maps(t_fdf *fdf, int argc, char **argv)
{
	ft_include_int_map(ft_get_char_map(argc, argv, fdf), &(fdf->s_map));
	ft_create_sub_map(&(fdf->c_map), &(fdf->s_map));
	ft_create_sub_map(&(fdf->h_map), &(fdf->s_map));
}

int		ft_precalculate(t_fdf *fdf, int action)
{
	int	i;
	int	j;

	if (fdf->params.cell_range < 3)
		fdf->params.cell_range = 3;
	if (fdf->params.cell_range > WIN_WIDTH / 2)
		fdf->params.cell_range = WIN_WIDTH / 2;
	if ((fdf->params.cell_range == 3 && action == REDUCE) || (fdf->params.cell_range == WIN_WIDTH / 2 && action == INCREASE))
		return (1);
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
	return (0);
}

void	ft_recalculate_points(t_fdf *fdf, int action)
{
	int	i;
	int	j;

	if (ft_precalculate(fdf, action))
		return ;
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

	fdf->params.cell_range = (WIN_WIDTH * 90 / 100) / fdf->s_map.width;
	fdf->params.left = -(fdf->s_map.width * fdf->params.cell_range) / 2;
	fdf->params.top = -(fdf->s_map.height * fdf->params.cell_range) / 2;
	fdf->params.peak_height = fdf->h_map.points[0][0].z;
	fdf->params.bottom_height = fdf->h_map.points[0][0].z;
	i = -1;
	while (++i < fdf->s_map.height)
	{
		j = -1;
		while (++j < fdf->s_map.width)
		{
			if (fdf->h_map.points[i][j].z > fdf->params.peak_height)
				fdf->params.peak_height = fdf->h_map.points[i][j].z;
			if (fdf->h_map.points[i][j].z < fdf->params.bottom_height)
				fdf->params.bottom_height = fdf->h_map.points[i][j].z;
			fdf->s_map.points[i][j].x = fdf->params.left + fdf->params.cell_range * j;
			fdf->s_map.points[i][j].y = fdf->params.top + fdf->params.cell_range * i;
			fdf->s_map.points[i][j].z *= fdf->params.cell_range;
		}
	}
	fdf->params.middle_height = (fdf->params.peak_height + fdf->params.bottom_height) / 2;
	ft_reset_current_map(fdf);
}
