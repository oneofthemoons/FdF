#include "fdf.h"
#include "libft.h"

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

void	ft_init_drawer(t_pos *from, t_pos *to, t_pos *delta, int *error)
{
	if (from->x > to->x)
		ft_swap_pos(from, to);
	delta->x = abs(to->x - from->x);
	delta->y = abs(to->y - from->y);
	*error = 0;
	delta->z = delta->y;
}

void	ft_init_direction(int *dir_y, t_pos *to, t_pos *from, t_pos *cur)
{
	*dir_y = to->y - from->y;
	if (*dir_y > 0)
		*dir_y = 1;
	else if (*dir_y < 0)
		*dir_y = -1;
	ft_copy_pos(from, cur);
}

void	ft_delta_render(t_pos2 *d, t_pos2 *sign_d, t_pos *from, t_pos *to)
{
	int	sign;
	int	f;

	f = 0;
	sign = abs(d->y) <= abs(d->x);
	while (from->x != to->x || from->y != to->y)
	{
		f += sign ? d->y * sign_d->y : d->x * sign_d->x;
		if (f > 0)
		{
			f -= sign ? d->x * sign_d->x : d->y * sign_d->y;
			if (sign)
				from->y += sign_d->y;
			else
				from->x -= sign_d->x;
		}
		if (sign)
			from->x -= sign_d->x;
		else
			from->y += sign_d->y;
	}
}

void	ft_draw_line(t_fdf *fdf, t_pos from, t_pos to)
{
	t_pos2	d;
	t_pos2	sign_d;
	int	f;
	int	sign;

	d.y = to.y - from.y;
	d.x = from.x - to.x;
	sign_d.y = d.y < 0 ? -1 : 1;
	sign_d.x = d.x < 0 ? -1 : 1;
	f = 0;
	sign = abs(d.y) <= abs(d.x);
	while (from.x != to.x || from.y != to.y)
	{
		f += sign ? d.y * sign_d.y : d.x * sign_d.x;
		if (f > 0)
		{
			f -= sign ? d.x * sign_d.x : d.y * sign_d.y;
			if (sign)
				from.y += sign_d.y;
			else
				from.x -= sign_d.x;
		}
		if (sign)
			from.x -= sign_d.x;
		else
			from.y += sign_d.y;
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, from.x, from.y, 0xFFFFFF);
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
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, pos.x, pos.y, 0xFFFFFF);
		}
	}
}

void	ft_draw_cells(t_fdf *fdf)
{
	t_pos	iter;
	t_pos	from;
	t_pos	to;

	iter.y = -1;
	while (++(iter.y) < fdf->c_map.height)
	{
		iter.x = -1;
		while (++(iter.x) < fdf->c_map.width)
		{
			from.x = fdf->c_map.points[iter.y][iter.x].x;
			from.y = fdf->c_map.points[iter.y][iter.x].y;
			if (iter.y < fdf->c_map.height - 1)
			{
				to.x = fdf->c_map.points[iter.y + 1][iter.x].x;
				to.y = fdf->c_map.points[iter.y + 1][iter.x].y;
				ft_draw_line(fdf, from, to);
			}
			if (iter.x < fdf->c_map.width - 1)
			{
				to.x = fdf->c_map.points[iter.y][iter.x + 1].x;
				to.y = fdf->c_map.points[iter.y][iter.x + 1].y;
				ft_draw_line(fdf, from, to);
			}
		}
	}
}

void	ft_rotate_x(t_fdf *fdf)
{
	int		i;
	int		j;
	float	cs;
	float	sn;

	cs = cos(fdf->params.angle.x);
	sn = sin(fdf->params.angle.x);
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			fdf->c_map.points[i][j].y = fdf->s_map.points[i][j].y * cs + fdf->s_map.points[i][j].z * sn;
			fdf->c_map.points[i][j].z = -(fdf->s_map.points[i][j].y) * sn + fdf->s_map.points[i][j].z * cs;
		}
	}
}

void	ft_rotate_y(t_fdf *fdf)
{
	int		i;
	int		j;
	float	cs;
	float	sn;

	cs = cos(fdf->params.angle.y);
	sn = sin(fdf->params.angle.y);
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			fdf->c_map.points[i][j].x = fdf->c_map.points[i][j].x * cs + fdf->c_map.points[i][j].z * sn;
			fdf->c_map.points[i][j].z = -(fdf->c_map.points[i][j].x) * sn + fdf->c_map.points[i][j].z * cs;
		}
	}
}

void	ft_rotate_z(t_fdf *fdf)
{
	int		i;
	int		j;
	float	cs;
	float	sn;
	int		x;

	i = -1;
	cs = cos(fdf->params.angle.z);
	sn = sin(fdf->params.angle.z);
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			x = fdf->c_map.points[i][j].x;
			fdf->c_map.points[i][j].x = fdf->c_map.points[i][j].x * cs - fdf->c_map.points[i][j].y * sn;
			fdf->c_map.points[i][j].y = x * sn + fdf->c_map.points[i][j].y * cs;
		}
	}
}

void	ft_search_walls(t_fdf *fdf, t_walls *walls)
{
	int	i;
	int	j;

	ft_init_walls(walls);
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			if (fdf->c_map.points[i][j].x < walls->left || walls->left == -1)
				walls->left = fdf->c_map.points[i][j].x;
			if (fdf->c_map.points[i][j].x > walls->right || walls->right == -1)
				walls->right = fdf->c_map.points[i][j].x;
			if (fdf->c_map.points[i][j].y < walls->down || walls->down == -1)
				walls->down = fdf->c_map.points[i][j].y;
			if (fdf->c_map.points[i][j].y > walls->top || walls->top == -1)
				walls->top = fdf->c_map.points[i][j].y;
		}
	}
}

void	ft_central(t_fdf *fdf)
{
	t_walls	walls;
	int		i;
	int		j;

	ft_search_walls(fdf, &walls);
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			fdf->c_map.points[i][j].x += (WIN_WIDTH - walls.right + walls.left) / 2 - walls.left;
			fdf->c_map.points[i][j].y += (WIN_HEIGHT - walls.down + walls.top) / 2 - walls.top;
		}
	}
}

int		ft_deal_key(int key, void *fdf)
{
	//printf("key: %d\n", key);
	if (key == 53)
		exit(0);
	mlx_clear_window(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->win_ptr);
	if (key == 15)
		ft_reset_fpos(&(((t_fdf*)fdf)->params.angle));
	if (key == 13)
		((t_fdf*)fdf)->params.angle.x -= ANGLE;
	if (key == 1)
		((t_fdf*)fdf)->params.angle.x += ANGLE;
	if (key == 2)
		((t_fdf*)fdf)->params.angle.y += ANGLE;
	if (key == 0)
		((t_fdf*)fdf)->params.angle.y -= ANGLE;
	if (key == 14)
		((t_fdf*)fdf)->params.angle.z += ANGLE;
	if (key == 12)
		((t_fdf*)fdf)->params.angle.z -= ANGLE;
	if (key == 126)
		ft_recalculate_points((t_fdf*)fdf, INCREASE);
	if (key == 125)
		ft_recalculate_points((t_fdf*)fdf, REDUCE);
	if (key == 13 || key == 1 || key == 2 || key == 0 || key == 15
		|| key == 12 || key == 14 || key == 125 || key == 126)
	{
		ft_reset_current_map((t_fdf*)fdf);
		ft_rotate_x((t_fdf*)fdf);
		ft_rotate_y((t_fdf*)fdf);
		ft_rotate_z((t_fdf*)fdf);
		ft_central((t_fdf*)fdf);
	}
	ft_draw_points((t_fdf*)fdf);
	ft_draw_cells((t_fdf*)fdf);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf.c_map.points = NULL;
	ft_create_maps(&fdf, argc, argv);
	ft_reset_current_map(&fdf);
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "PUPA_WIN_A");
	ft_calculate_params(&fdf);
	ft_central(&fdf);
	ft_draw_points(&fdf);
	ft_draw_cells(&fdf);
    mlx_key_hook(fdf.win_ptr, ft_deal_key, (void*)(&fdf));
    mlx_loop(fdf.mlx_ptr);
}