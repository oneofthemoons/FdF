#ifndef FDF_H
# define FDF_H
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280
# define PIXEL_RANGE 1
# define BUFF_FDF 4096
# define ANGLE 0.01
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"


#include <stdio.h> //deb

typedef struct  s_pos
{
	int			x;
	int			y;
	int			z;
}               t_pos;

typedef struct  s_fpos
{
	float		x;
	float		y;
	float		z;
}               t_fpos;

typedef struct	s_map
{
	t_pos		**points;
	int			width;
	int			height;
}				t_map;

typedef struct	s_params
{
	int			cell_range;
	int			left;
	int			top;
	t_fpos		angle;
}				t_params;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		s_map;
	t_map		c_map;
	t_params	params;
}				t_fdf;


void	ft_print_error(char* strerr);
void	ft_reset_current_map(t_fdf *fdf);
void	ft_create_maps(t_fdf *fdf, int argc, char **argv);
void	ft_include_int_map(char* c_map, t_map *map);
void	ft_set_pos(t_pos *pos, int x, int y, int z);
void	ft_reset_pos(t_pos *pos);
void	ft_free_string_arr(char **arr);
void	ft_free_map(t_map *map);
int		ft_map_check(int argc, char **argv);
char	*ft_get_char_map(char *filename);
void	ft_calculate_params(t_fdf *fdf);
void	ft_copy_pos(const t_pos *from, t_pos *to);
void	ft_swap_pos(t_pos *pos1, t_pos *pos2);

#endif