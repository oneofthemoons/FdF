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
	int					top;
	int					left;
	int					down;
	int					right;
}						t_walls;

typedef struct  		s_pos
{
	int					x;
	int					y;
	int					z;
	int					color;
	int					src_color;
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
	int					width;
	int					height;
}						t_map;

typedef struct			s_params
{
	int					cell_range;
	int					left;
	int					top;
	int					peak_height;
	int					middle_height;
	int					bottom_height;
	t_fpos				angle;
}						t_params;

typedef struct			s_image
{
	void				*ptr;
	char				*str;
	int					bpp;
	int					size_line;
	int					endian;
}						t_image;

typedef enum			e_projection
{
	PARALLEL,
	ISO
}						t_projection;

typedef struct			s_fdf
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_map				s_map;
	t_map				c_map;
	t_map				h_map;
	t_params			params;
	t_image				img;
	t_projection		projection;
}						t_fdf;

typedef struct			s_line_color
{
	t_pos2				idx_from;
	t_pos2				idx_to;
}						t_line_color;

void					ft_print_error(char* strerr);
void					ft_reset_current_map(t_fdf *fdf);
void					ft_create_maps(t_fdf *fdf, int argc, char **argv);
void					ft_include_int_map(char* c_map, t_map *map);
void					ft_set_pos(t_pos *pos, int x, int y, int z);
void					ft_free_string_arr(char **arr);
void					ft_free_map(t_map *map);
char					*ft_get_char_map(int argc, char **argv, t_fdf *fdf);
void					ft_calculate_params(t_fdf *fdf);
void					ft_reset_fpos(t_fpos *pos);
void					ft_init_walls(t_walls *walls);
void					ft_central(t_fdf *fdf);
void					ft_recalculate_points(t_fdf *fdf, int action);
void					ft_init_h_map(t_fdf *fdf);
int						ft_max(int a, int b);

#endif