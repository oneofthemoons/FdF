/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:47:56 by hrickard          #+#    #+#             */
/*   Updated: 2019/03/30 15:47:58 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_create_sub_map(t_map *c_map, const t_map *s_map)
{
	int	i;

	c_map->height = s_map->height;
	c_map->width = s_map->width;
	c_map->points = (t_pos**)malloc(sizeof(t_pos**) * c_map->height);
	i = -1;
	while (++i < c_map->height)
		c_map->points[i] = (t_pos*)malloc(sizeof(t_pos) * c_map->width);
}

void	ft_init_h_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->h_map.height)
	{
		j = -1;
		while (++j < fdf->h_map.width)
			ft_set_pos(&(fdf->h_map.points[i][j]), fdf->s_map.points[i][j].x,
				fdf->s_map.points[i][j].y, fdf->s_map.points[i][j].z);
	}
}

void	ft_create_maps(t_fdf *fdf, int argc, char **argv)
{
	ft_include_int_map(ft_get_char_map(argc, argv, fdf), &(fdf->s_map));
	ft_create_sub_map(&(fdf->c_map), &(fdf->s_map));
	ft_create_sub_map(&(fdf->h_map), &(fdf->s_map));
}

void	ft_params_init(t_fdf *fdf)
{
	fdf->params.cell_range = (90 * WIN_WIDTH / 100) / fdf->s_map.width;
	fdf->params.left = -(fdf->s_map.width * fdf->params.cell_range) / 2;
	fdf->params.top = -(fdf->s_map.height * fdf->params.cell_range) / 2;
	fdf->params.peak_height = fdf->h_map.points[0][0].z;
	fdf->params.bottom_height = fdf->h_map.points[0][0].z;
}

void	ft_calculate_params(t_fdf *fdf)
{
	int	i;
	int	j;

	ft_params_init(fdf);
	i = -1;
	while (++i < fdf->s_map.height)
	{
		j = -1;
		while (++j < fdf->s_map.width)
		{
			if (fdf->h_map.points[i][j].z > fdf->params.peak_height)
				fdf->params.peak_height = fdf->h_map.points[i][j].z;
			if (fdf->h_map.points[i][j].z < fdf->params.bottom_height)
				fdf->params.bottom_height = fdf->h_map.points[i][j].z;
			fdf->s_map.points[i][j].x = fdf->params.left +
				fdf->params.cell_range * j;
			fdf->s_map.points[i][j].y = fdf->params.top +
				fdf->params.cell_range * i;
			fdf->s_map.points[i][j].z *= fdf->params.cell_range;
		}
	}
	fdf->params.mid_height = (fdf->params.peak_height +
		fdf->params.bottom_height) / 2;
	ft_reset_current_map(fdf);
}
