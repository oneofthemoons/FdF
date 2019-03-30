#include "fdf.h"

void	ft_init_walls(t_walls *walls)
{
	walls->top = -1;
	walls->left = -1;
	walls->down = -1;
	walls->right = -1;
}

int		ft_max(int a, int b)
{
	return (a > b ? a : b);
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
