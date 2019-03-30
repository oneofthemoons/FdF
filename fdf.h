#ifndef FDF_H
# define FDF_H
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define PIXEL_RANGE 1
# define BUFF_FDF 4096
# define ANGLE 0.05
# define REDUCE -1
# define INCREASE 1
# define GREEN 0x008000
# define BROWN 0x964b00
# define WHITE 0xFFFFFF
# define CLR_ERROR -2
# define NO_COLOR -1
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"


#include <stdio.h> //deb

typedef unsigned char	u_ch;

typedef struct			s_walls
{
	int					right;
	int					left;
	int					down;
	int					top;
}						t_walls;

typedef struct  		s_pos
{
	int					src_color;
	int					color;
	int					x;
	int					y;
	int					z;
}       		        t_pos;

typedef struct			s_fpos
{
	float				x;
	float				y;
	float				z;
}						t_fpos;

typedef struct			s_pos2
{
	int					x;
	int					y;
}						t_pos2;

typedef struct			s_map
{
	t_pos				**points;
	int					height;
	int					width;
}						t_map;

typedef struct			s_params
{
	t_fpos				angle;
	int					bottom_height;
	int					middle_height;
	int					peak_height;
	int					cell_range;
	int					left;
	int					top;
}						t_params;

typedef struct			s_image
{
	void				*ptr;
	char				*str;
	int					size_line;
	int					endian;
	int					bpp;
}						t_image;

typedef enum			e_projection
{
	PARALLEL,
	ISO
}						t_projection;

typedef struct			s_respect
{
	int					height;
	int					width;
	void				*ptr;
}						t_respect;


typedef struct			s_fdf
{
	t_projection		projection;
	t_respect			respect;
	t_params			params;
	t_image				img;
	t_map				s_map;
	t_map				c_map;
	t_map				h_map;
	void				*mlx_ptr;
	void				*win_ptr;
	int					is_respect;
}						t_fdf;

typedef struct			s_line_color
{
	t_pos				from;
	t_pos				to;
}						t_line_color;

void					ft_set_start_current_d_pos(t_pos2 *current, t_pos2 *d, t_pos *to, t_pos *from);
void					ft_start_sign(t_pos2 *sign_d, t_pos2 *d, int *sign, int *f);
void					ft_create_maps(t_fdf *fdf, int argc, char **argv);
void					ft_put_pixel(t_fdf *fdf, int x, int y, int color);
void					ft_draw_line(t_fdf *fdf, t_pos from, t_pos to);
void					ft_recalculate_points(t_fdf *fdf, int action);
void					ft_include_int_map(char* c_map, t_map *map);
void					ft_set_pos(t_pos *pos, int x, int y, int z);
void					ft_search_walls(t_fdf *fdf, t_walls *walls);
void					ft_reset_current_map(t_fdf *fdf);
void					ft_calculate_params(t_fdf *fdf);
void					ft_free_string_arr(char **arr);
void					ft_init_walls(t_walls *walls);
void					ft_print_error(char* strerr);
void					ft_create_image(t_fdf *fdf);
void					ft_draw_points(t_fdf *fdf);
void					ft_reset_fpos(t_fpos *pos);
void					ft_clear_image(t_fdf *fdf);
void					ft_instruction(t_fdf *fdf);
void					ft_init_h_map(t_fdf *fdf);
void					ft_draw_cells(t_fdf *fdf);
void					ft_free_map(t_map *map);
void					ft_rotate_x(t_fdf *fdf);
void					ft_rotate_y(t_fdf *fdf);
void					ft_rotate_z(t_fdf *fdf);
void					ft_central(t_fdf *fdf);
void					ft_set_iso(t_fdf *fdf);
void					ft_central(t_fdf *fdf);
char					*ft_get_char_map(int argc, char **argv, t_fdf *fdf);
int						ft_get_line_color(t_pos from, t_pos to, t_pos2 current);
int						ft_get_point_color(t_fdf *fdf, int height);
int						ft_precalculate(t_fdf *fdf, int action);
int						ft_max(int a, int b);
int						ft_close(void *fdf);

#endif