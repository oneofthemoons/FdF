#ifndef FDF_H
# define FDF_H
# define WIN_HEIGHT 480
# define WIN_WIDTH 640
# define PIXEL_RANGE 1
# define BUFF_FDF 4096
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>


#include <stdio.h> //deb

typedef struct  s_pos
{
	int			x;
	int			y;
	int			z;
	void		*ft_set_pos;
}               t_pos;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_pos		cur_pos;
}				t_fdf;

typedef struct	s_map
{
	t_pos		**points;
	int			width;
	int			height;
}				t_map;



#endif