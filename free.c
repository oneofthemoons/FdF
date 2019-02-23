#include "fdf.h"


void	ft_free_string_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->height)
		free(map->points[i]);
	free(map->points);
}