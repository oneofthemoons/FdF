#include "fdf.h"

void	ft_reset_pos(t_pos *pos)
{
	pos->x = 0;
	pos->y = 0;
	pos->z = 0;
}

void	ft_set_pos(t_pos *pos, int x, int y, int z)
{
	pos->x = x;
	pos->y = y;
	pos->z = z;
}