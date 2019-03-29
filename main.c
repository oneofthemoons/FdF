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

void	ft_clear_image(t_fdf *fdf)
{
	ft_bzero(fdf->img.str, fdf->img.size_line * WIN_HEIGHT);
}

void	ft_create_image(t_fdf *fdf)
{
	fdf->img.ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.str = mlx_get_data_addr(fdf->img.ptr, &(fdf->img.bpp), &(fdf->img.size_line), &(fdf->img.endian));
	ft_clear_image(fdf);
}

void	ft_put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char			*pixel;
	unsigned int	clr;
	int				i;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	pixel = &(fdf->img.str[y * fdf->img.size_line + x * (fdf->img.bpp / 8)]);
	clr = mlx_get_color_value(fdf->mlx_ptr, color);
	i = -1;
	while (++i < fdf->img.bpp / 8)
		pixel[i] = ((char*)(&clr))[i];
}

int ft_close(void *fdf)
{
	int	i;

	i = -1;
	while (++i < ((t_fdf*)fdf)->s_map.height)
	{
		free(((t_fdf*)fdf)->c_map.points[i]);
		free(((t_fdf*)fdf)->h_map.points[i]);
		free(((t_fdf*)fdf)->s_map.points[i]);
	}
	free(((t_fdf*)fdf)->c_map.points);
	free(((t_fdf*)fdf)->s_map.points);
	free(((t_fdf*)fdf)->h_map.points);
	mlx_destroy_image(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->respect.ptr);
	mlx_destroy_image(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->img.ptr);
	mlx_destroy_window(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->win_ptr);
	exit(0);
	return (0);
}

int		ft_get_point_color(t_fdf *fdf, int height)
{
	int		color;
	int		delta;
	int		*c_ptr;

	c_ptr = &color;
	if (height < fdf->params.middle_height)
	{
		delta = fdf->params.middle_height - fdf->params.bottom_height; 
		if (!delta || height == fdf->params.bottom_height)
			return (GREEN);
		color = 0;
		((char*)c_ptr)[1] = (char)(0x80 - (height * (0x80 - 0x4b)) / (delta));
		((char*)c_ptr)[2] = (char)(0x00 + (height * (0x96 - 0x00)) / (delta));
		return (color);
	}
	delta = fdf->params.peak_height - fdf->params.middle_height;
	if (!delta)
		return (WHITE);
	color = 0;
	((char*)c_ptr)[0] = (char)(0x00 + ((height - fdf->params.middle_height) * (0xFF - 0x00)) / (delta));
	((char*)c_ptr)[1] = (char)(0x4b + ((height - fdf->params.middle_height) * (0xFF - 0x4b)) / (delta));
	((char*)c_ptr)[2] = (char)(0x96 + ((height - fdf->params.middle_height) * (0xFF - 0x96)) / (delta));
	return (color);
}

int		ft_get_line_color(t_pos from, t_pos to, t_pos2 current)
{
	t_pos2	d;
	int		d_cur;
	int		color;
	int		d_max;
	int		i;

	d.x = abs(to.x - from.x);
	d.y = abs(to.y - from.y);
	d_cur = d.x > d.y ? abs(current.x - from.x) : abs(current.y - from.y);
	d_max = ft_max(d.x, d.y);
	color = 0;
	i = -1;
	while (++i < 3)
		((u_ch*)(&color))[i] = ((u_ch*)(&(from.color)))[i] + ((((u_ch*)(&(to.color)))[i] - ((u_ch*)(&(from.color)))[i]) * d_cur) / d_max;
	return (color);
}

void	ft_draw_line(t_fdf *fdf, t_pos from, t_pos to)
{
	t_pos2	d;
	t_pos2	sign_d;
	t_pos2	current;
	int	f;
	int	sign;

	current.x = from.x;
	current.y = from.y;
	d.y = to.y - from.y;
	d.x = from.x - to.x;
	sign_d.y = d.y < 0 ? -1 : 1;
	sign_d.x = d.x < 0 ? -1 : 1;
	f = 0;
	sign = abs(d.y) <= abs(d.x);
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
	t_pos			from;
	t_pos			to;
	t_line_color	color;

	iter.y = -1;
	while (++(iter.y) < fdf->c_map.height)
	{
		iter.x = -1;
		while (++(iter.x) < fdf->c_map.width)
		{
			from = fdf->c_map.points[iter.y][iter.x];
			if (iter.y < fdf->c_map.height - 1)
			{
				to = fdf->c_map.points[iter.y + 1][iter.x];
				color.idx_from = iter;
				color.idx_to.x = iter.x;
				color.idx_to.y = iter.y + 1;
				ft_draw_line(fdf, from, to);
			}
			if (iter.x < fdf->c_map.width - 1)
			{
				to = fdf->c_map.points[iter.y][iter.x + 1];
				color.idx_from = iter;
				color.idx_to.x = iter.x + 1;
				color.idx_to.y = iter.y;
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

void	ft_set_iso(t_fdf *fdf)
{
	int		i;
	int		j;
	int		x;
	float	sn;
	float	cs;

	sn = sin(0.523599);
	cs = cos(0.523599);
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			x = fdf->c_map.points[i][j].x;
			fdf->c_map.points[i][j].x = (x - fdf->c_map.points[i][j].y) * cs;
			fdf->c_map.points[i][j].y = (x + fdf->c_map.points[i][j].y) * sn - fdf->c_map.points[i][j].z;
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

void	ft_str_instuct(t_fdf *fdf, char *str, int line)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, WIN_WIDTH / 48, WIN_HEIGHT - (WIN_HEIGHT / 3.5 - line * 20), 0xFFFAFA, str);
}

void	ft_instruction(t_fdf *fdf)
{
	ft_str_instuct(fdf, "Press:", -2);
	ft_str_instuct(fdf, "ESC to exit", 0);
	ft_str_instuct(fdf, "I to choose ISO projection", 1);
	ft_str_instuct(fdf, "P to choose PARALLEL projection", 2);
	ft_str_instuct(fdf, "F to pay respect", 3);
	ft_str_instuct(fdf, "ARROW UP to zoom+", 4);
	ft_str_instuct(fdf, "ARROW DOWN to zoom-", 5);
	ft_str_instuct(fdf, "W/S to rotate in X axis (PARALLEL)", 6);
	ft_str_instuct(fdf, "D/A to rotate in Z axis (PARALLEL)", 7);
	ft_str_instuct(fdf, "Q/E to rotate in Y axis (PARALLEL)", 8);
}

void	ft_hook_parallel(int key, void *fdf)
{
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
}

void	ft_render_parallel(void *fdf)
{
	if (((t_fdf*)fdf)->projection == PARALLEL)
	{
			ft_rotate_x((t_fdf*)fdf);
			ft_rotate_y((t_fdf*)fdf);
			ft_rotate_z((t_fdf*)fdf);
	}
}

void	ft_hook_service(int key, void *fdf)
{
	if (key == 53 || ((t_fdf*)fdf)->is_respect)
		ft_close(fdf);
	if (key == 34)
		((t_fdf*)fdf)->projection = ISO;
	if (key == 35)
		((t_fdf*)fdf)->projection = PARALLEL;
	if (((t_fdf*)fdf)->projection == PARALLEL)
		ft_hook_parallel(key, fdf);
	if (key == 126)
		ft_recalculate_points((t_fdf*)fdf, INCREASE);
	if (key == 125)
		ft_recalculate_points((t_fdf*)fdf, REDUCE);
	if (key == 3)
		((t_fdf*)fdf)->is_respect = 1;
}

int		ft_deal_key(int key, void *fdf)
{
	mlx_clear_window(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->win_ptr);
	ft_clear_image((t_fdf*)fdf);
	ft_hook_service(key, fdf);
	if ((key >= 12 && key <= 15) || key == 1 || key == 2 || key == 0 ||
		key == 125 || key == 126 || key == 34 || key == 35)
	{
		ft_reset_current_map((t_fdf*)fdf);
		ft_render_parallel(fdf);
		if (((t_fdf*)fdf)->projection == ISO)
			ft_set_iso((t_fdf*)fdf);
		ft_central((t_fdf*)fdf);
	}
	if (((t_fdf*)fdf)->is_respect)
	{
		mlx_put_image_to_window(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->win_ptr, ((t_fdf*)fdf)->respect.ptr, WIN_WIDTH / 2 - 640, WIN_HEIGHT / 2 - 360);
		return (0);
	}
	ft_draw_points((t_fdf*)fdf);
	ft_draw_cells((t_fdf*)fdf);
	mlx_put_image_to_window(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->win_ptr, ((t_fdf*)fdf)->img.ptr, 0, 0);
	ft_instruction((t_fdf*)fdf);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf.projection = PARALLEL;
	fdf.c_map.points = NULL;
	ft_create_maps(&fdf, argc, argv);
	ft_reset_current_map(&fdf);
	ft_init_h_map(&fdf);
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "PUPA_WIN_A");
	ft_calculate_params(&fdf);
	fdf.is_respect = 0;
	fdf.respect.ptr = mlx_xpm_file_to_image(fdf.mlx_ptr, "./drawable/respect.xpm", &(fdf.respect.width), &(fdf.respect.height));
	ft_central(&fdf);
	ft_create_image(&fdf);
	ft_draw_points(&fdf);
	ft_draw_cells(&fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img.ptr, 0, 0);
	ft_instruction(&fdf);
    mlx_key_hook(fdf.win_ptr, ft_deal_key, (void*)(&fdf));
	mlx_hook(fdf.win_ptr, 17, 0, ft_close, (void*)(&fdf));
    mlx_loop(fdf.mlx_ptr);
}