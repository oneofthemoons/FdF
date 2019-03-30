#include "fdf.h"

void	ft_set_start_current_d_pos(t_pos2 *current, t_pos2 *d, t_pos *to, t_pos *from)
{
	current->x = from->x;
	current->y = from->y;
	d->y = to->y - from->y;
	d->x = from->x - to->x;
}

void	ft_start_sign(t_pos2 *sign_d, t_pos2 *d, int *sign, int *f)
{
	sign_d->y = d->y < 0 ? -1 : 1;
	sign_d->x = d->x < 0 ? -1 : 1;
	*sign = abs(d->y) <= abs(d->x);
	*f = 0;
}

void	ft_draw_line(t_fdf *fdf, t_pos from, t_pos to)
{
	t_pos2	d;
	t_pos2	sign_d;
	t_pos2	current;
	int	f;
	int	sign;

	ft_set_start_current_d_pos(&current, &d, &to, &from);
	ft_start_sign(&sign_d, &d, &sign, &f);
	while (current.x != to.x || current.y != to.y)
	{
		f += sign ? d.y * sign_d.y : d.x * sign_d.x;
		if (f > 0)
		{
			f -= sign ? d.x * sign_d.x : d.y * sign_d.y;
			if (sign)
				current.y += sign_d.y;
			else
				current.x -= sign_d.x;
		}
		if (sign)
			current.x -= sign_d.x;
		else
			current.y += sign_d.y;
		ft_put_pixel(fdf, current.x, current.y, ft_get_line_color(from, to, current));
	}
}

void	ft_draw_points(t_fdf *fdf)
{
	int		i;
	int		j;
	t_pos	pos;

	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			pos.x = fdf->c_map.points[i][j].x;
			pos.y = fdf->c_map.points[i][j].y;
			fdf->c_map.points[i][j].color = fdf->c_map.points[i][j].src_color == -1 ?
				ft_get_point_color(fdf, fdf->h_map.points[i][j].z) :
				fdf->c_map.points[i][j].src_color;
			ft_put_pixel(fdf, pos.x, pos.y, fdf->c_map.points[i][j].color);
		}
	}
}

void	ft_draw_cells(t_fdf *fdf)
{
	t_pos2			iter;
	t_line_color	color;

	iter.y = -1;
	while (++(iter.y) < fdf->c_map.height)
	{
		iter.x = -1;
		while (++(iter.x) < fdf->c_map.width)
		{
			color.from = fdf->c_map.points[iter.y][iter.x];
			if (iter.y < fdf->c_map.height - 1)
			{
				color.to = fdf->c_map.points[iter.y + 1][iter.x];
				ft_draw_line(fdf, color.from, color.to);
			}
			if (iter.x < fdf->c_map.width - 1)
			{
				color.to = fdf->c_map.points[iter.y][iter.x + 1];
				ft_draw_line(fdf, color.from, color.to);
			}
		}
	}
}
