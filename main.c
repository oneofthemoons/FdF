#include "fdf.h"

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
	ft_reset_fpos(&fdf.params.angle);
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