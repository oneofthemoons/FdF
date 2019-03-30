#include "fdf.h"

int		ft_get_point_color(t_fdf *fdf, int height)
{
	int		color;
	int		delta;
	int		*c_ptr;

	c_ptr = &color;
	if (height < fdf->params.middle_height)
	{
		delta = fdf->params.middle_height - fdf->params.bottom_height; 
		if (!delta || height == fdf->params.bottom_height)
			return (GREEN);
		color = 0;
		((char*)c_ptr)[1] = (char)(0x80 - (height * (0x80 - 0x4b)) / (delta));
		((char*)c_ptr)[2] = (char)(0x00 + (height * (0x96 - 0x00)) / (delta));
		return (color);
	}
	delta = fdf->params.peak_height - fdf->params.middle_height;
	if (!delta)
		return (WHITE);
	color = 0;
	((char*)c_ptr)[0] = (char)(0x00 + ((height - fdf->params.middle_height) * (0xFF - 0x00)) / (delta));
	((char*)c_ptr)[1] = (char)(0x4b + ((height - fdf->params.middle_height) * (0xFF - 0x4b)) / (delta));
	((char*)c_ptr)[2] = (char)(0x96 + ((height - fdf->params.middle_height) * (0xFF - 0x96)) / (delta));
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
		((u_ch*)(&color))[i] = ((u_ch*)(&(from.color)))[i] + ((((u_ch*)(&(to.color)))[i] - ((u_ch*)(&(from.color)))[i]) * d_cur) / d_max;
	return (color);
}
