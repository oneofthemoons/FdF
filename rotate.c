/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:48:14 by hrickard          #+#    #+#             */
/*   Updated: 2019/03/30 15:48:16 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate_x(t_fdf *fdf)
{
	int		i;
	int		j;
	float	cs;
	float	sn;

	cs = cos(fdf->params.angle.x);
	sn = sin(fdf->params.angle.x);
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			fdf->c_map.points[i][j].y = fdf->s_map.points[i][j].y * cs +
				fdf->s_map.points[i][j].z * sn;
			fdf->c_map.points[i][j].z = -(fdf->s_map.points[i][j].y) * sn +
				fdf->s_map.points[i][j].z * cs;
		}
	}
}

void	ft_rotate_y(t_fdf *fdf)
{
	int		i;
	int		j;
	float	cs;
	float	sn;

	cs = cos(fdf->params.angle.y);
	sn = sin(fdf->params.angle.y);
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			fdf->c_map.points[i][j].x = fdf->c_map.points[i][j].x * cs +
				fdf->c_map.points[i][j].z * sn;
			fdf->c_map.points[i][j].z = -(fdf->c_map.points[i][j].x) * sn +
				fdf->c_map.points[i][j].z * cs;
		}
	}
}

void	ft_rotate_z(t_fdf *fdf)
{
	int		i;
	int		j;
	float	cs;
	float	sn;
	int		x;

	i = -1;
	cs = cos(fdf->params.angle.z);
	sn = sin(fdf->params.angle.z);
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			x = fdf->c_map.points[i][j].x;
			fdf->c_map.points[i][j].x = fdf->c_map.points[i][j].x * cs -
				fdf->c_map.points[i][j].y * sn;
			fdf->c_map.points[i][j].y = x * sn + fdf->c_map.points[i][j].y * cs;
		}
	}
}

void	ft_set_iso(t_fdf *fdf)
{
	int		i;
	int		j;
	int		x;
	float	sn;
	float	cs;

	sn = sin(0.523599);
	cs = cos(0.523599);
	i = -1;
	while (++i < fdf->c_map.height)
	{
		j = -1;
		while (++j < fdf->c_map.width)
		{
			x = fdf->c_map.points[i][j].x;
			fdf->c_map.points[i][j].x = (x - fdf->c_map.points[i][j].y) * cs;
			fdf->c_map.points[i][j].y = (x + fdf->c_map.points[i][j].y) * sn -
				fdf->c_map.points[i][j].z;
		}
	}
}
