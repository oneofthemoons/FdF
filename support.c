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

int		ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int		ft_abs_ch(char a)
{
	return(a >= 0 ? a : -a);
}