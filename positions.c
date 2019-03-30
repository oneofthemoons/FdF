#include "fdf.h"

void	ft_reset_fpos(t_fpos *pos)
{
	pos->x = 0.f;
	pos->y = 0.f;
	pos->z = 0.f;
}

void	ft_set_pos(t_pos *pos, int x, int y, int z)
{
	pos->x = x;
	pos->y = y;
	pos->z = z;
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
