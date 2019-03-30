#include "fdf.h"

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