#include "fdf.h"
#include "libft.h"

int ft_deal_key(int key, void *mlx)
{
	if (key == 53)
		exit(0);
	if (key == 1 && ((t_fdf*)mlx)->cur_pos.y < WIN_HEIGHT)
		((t_fdf*)mlx)->cur_pos.y += PIXEL_RANGE;
	else if (key == 2 && ((t_fdf*)mlx)->cur_pos.x < WIN_WIDTH)
		((t_fdf*)mlx)->cur_pos.x += PIXEL_RANGE;
	else if (key == 13 && ((t_fdf*)mlx)->cur_pos.y > 0)
		((t_fdf*)mlx)->cur_pos.y -= PIXEL_RANGE;
	else if (key == 0 && ((t_fdf*)mlx)->cur_pos.x > 0)
		((t_fdf*)mlx)->cur_pos.x -= PIXEL_RANGE;
	mlx_pixel_put(((t_fdf*)mlx)->mlx_ptr, ((t_fdf*)mlx)->win_ptr, ((t_fdf*)mlx)->cur_pos.x, ((t_fdf*)mlx)->cur_pos.y, 0xFFFFFF);
	return (0);
}

void	ft_print_map_to_debug(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			ft_putnbr(map->points[i][j].z);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}


int main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf.c_map.points = NULL;
	ft_create_maps(&fdf, argc, argv);
	ft_reset_current_map(&fdf);
	ft_print_map_to_debug(&(fdf.c_map));
	ft_reset_pos(&(fdf.cur_pos));
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "PUPA_WIN_A");
    mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, fdf.cur_pos.x, fdf.cur_pos.y, 0xFFFFFF);
    mlx_key_hook(fdf.win_ptr, ft_deal_key, (void*)(&fdf));
    mlx_loop(fdf.mlx_ptr);
}