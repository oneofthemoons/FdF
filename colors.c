/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:46:36 by hrickard          #+#    #+#             */
/*   Updated: 2019/03/30 15:46:39 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_get_point_color(t_fdf *fdf, int h)
{
	int		color;
	int		d;
	int		*c;

	c = &color;
	if (h < fdf->params.mid_height)
	{
		d = fdf->params.mid_height - fdf->params.bottom_height;
		if (!d || h == fdf->params.bottom_height)
			return (GREEN);
		color = 0;
		((char*)c)[1] = (char)(0x80 - (h * (0x80 - 0x4b)) / (d));
		((char*)c)[2] = (char)(0x00 + (h * (0x96 - 0x00)) / (d));
		return (color);
	}
	d = fdf->params.peak_height - fdf->params.mid_height;
	if (!d)
		return (WHITE);
	color = 0;
	((char*)c)[0] = 0x00 + ((h - fdf->params.mid_height) * (0xFF - 0x00)) / (d);
	((char*)c)[1] = 0x4b + ((h - fdf->params.mid_height) * (0xFF - 0x4b)) / (d);
	((char*)c)[2] = 0x96 + ((h - fdf->params.mid_height) * (0xFF - 0x96)) / (d);
	return (color);
}

int		ft_get_line_color(t_pos from, t_pos to, t_pos2 current)
{
	t_pos2	d;
	int		d_cur;
	int		color;
	int		d_max;
	int		i;

	d.x = abs(to.x - from.x);
	d.y = abs(to.y - from.y);
	d_cur = d.x > d.y ? abs(current.x - from.x) : abs(current.y - from.y);
	d_max = ft_max(d.x, d.y);
	color = 0;
	i = -1;
	while (++i < 3)
		((t_uch*)(&color))[i] = ((t_uch*)(&(from.color)))[i] +
			((((t_uch*)(&(to.color)))[i] - ((t_uch*)(&(from.color)))[i]) *
			d_cur) / d_max;
	return (color);
}
