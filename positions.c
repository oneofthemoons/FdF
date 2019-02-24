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

void	ft_copy_pos(const t_pos *from, t_pos *to)
{
	to->x = from->x;
	to->y = from->y;
	to->z = from->z;
}

void	ft_swap_pos(t_pos *pos1, t_pos *pos2)
{
	t_pos	t;

	t.x = pos1->x;
	t.y = pos1->y;
	pos1->x = pos2->x;
	pos1->y = pos2->y;
	pos2->x = t.x;
	pos2->y = t.y;
}