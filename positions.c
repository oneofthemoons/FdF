#include "fdf.h"

void	ft_reset_fpos(t_fpos *pos)
{
	pos->x = 0.f;
	pos->y = 0.f;
	pos->z = 0.f;
}

void	ft_set_pos(t_pos *pos, int x, int y, int z)
{
	pos->x = x;
	pos->y = y;
	pos->z = z;
}
