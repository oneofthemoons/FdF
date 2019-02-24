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

// delta.z == delta_error

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

// deprecated
// void	ft_draw_line(t_fdf *fdf, t_pos from, t_pos to)
// {
// 	t_pos	delta;
// 	int		error;
// 	t_pos	cur;
// 	int		dir_y;

// 	ft_init_drawer(&from, &to, &delta, &error);
// 	ft_init_direction(&dir_y, &to, &from, &cur);
// 	if (cur.x == to.x)
// 	{
// 		if (dir_y == -1)
// 			ft_swap_pos(&cur, &to);
// 		while (cur.y <= to.y)
// 			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, cur.x, cur.y++, 0xFFFFFF);
// 		return ;
// 	}
// 	while (cur.x <= to.x)
// 	{
// 		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, cur.x++, cur.y, 0xFFFFFF);
// 		error += delta.z;
// 		if (error * 2 >= delta.x)
// 		{
// 			cur.y += dir_y;
// 			error -= delta.x;
// 		}
// 	}
// }

void	ft_draw_line(t_fdf *fdf, t_pos from, t_pos to)
{
	int	a;
	int	b;
	int	sign;
	int	sign_a;
	int	sign_b;
	int	f;
	int	x;
	int	y;

	x = from.x;
	y = from.y;
	a = to.y - from.y;
	b = from.x - to.x;
	if (abs(a) > abs(b))
		sign = 1;
	else
		sign = -1;
	if (a < 0)
		sign_a = -1;
	else
		sign_a = 1;
	if (b < 0)
		sign_b = -1;
	else
		sign_b = 1;
	f = 0;
	if (sign == -1)
	{
		while (x != to.x || y != to.y)
		{
			f += a * sign_a;
			if (f > 0)
			{
				f -= b * sign_b;
				y += sign_a;
			}
			x -= sign_b;
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xFFFFFF);
		}
	}
	else
	{
		while (x != to.x || y != to.y)
		{
			f += b * sign_b;
			if (f > 0)
			{
				f -= a * sign_a;
				x -= sign_b;
			}
			y += sign_a;
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xFFFFFF);
		}
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

void	ft_rotate_x(t_fdf *fdf, float delta_angle)
{
	int	i;
	int	j;

	fdf->params.angle_x += delta_angle;
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			fdf->c_map.points[i][j].y = fdf->s_map.points[i][j].y * cos(fdf->params.angle_x) + fdf->c_map.points[i][j].z * sin(fdf->params.angle_x);
			fdf->c_map.points[i][j].z = -(fdf->s_map.points[i][j].y) * sin(fdf->params.angle_x) + fdf->c_map.points[i][j].z * cos(fdf->params.angle_x);
		}
	}
}

void	ft_rotate_y(t_fdf *fdf, float delta_angle)
{
	int	i;
	int	j;

	fdf->params.angle_y += delta_angle;
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			fdf->c_map.points[i][j].x = fdf->s_map.points[i][j].x * cos(fdf->params.angle_y) + fdf->c_map.points[i][j].z * sin(fdf->params.angle_y);
			fdf->c_map.points[i][j].z = -(fdf->s_map.points[i][j].x) * sin(fdf->params.angle_y) + fdf->c_map.points[i][j].z * cos(fdf->params.angle_y);
		}
	}
}

int		ft_deal_key(int key, void *fdf)
{
	if (key == 53)
		exit(0);
	mlx_clear_window(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->win_ptr);
	if (key == 13)
		ft_rotate_x((t_fdf*)fdf, -ANGLE);
	if (key == 1)
		ft_rotate_x((t_fdf*)fdf, ANGLE);
	if (key == 15)
		ft_reset_current_map((t_fdf*)fdf);
	if (key == 2)
		ft_rotate_y((t_fdf*)fdf, ANGLE);
	if (key == 0)
		ft_rotate_y((t_fdf*)fdf, -ANGLE);
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
	ft_draw_points(&fdf);
    mlx_key_hook(fdf.win_ptr, ft_deal_key, (void*)(&fdf));
    mlx_loop(fdf.mlx_ptr);
}