#include "fdf.h"

void	ft_init_walls(t_walls *walls)
{
	walls->top = -1;
	walls->left = -1;
	walls->down = -1;
	walls->right = -1;
}

int		ft_max(int a, int b)
{
	return (a > b ? a : b);
}