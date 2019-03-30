/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:01:19 by hrickard          #+#    #+#             */
/*   Updated: 2019/03/30 17:01:21 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_check_color(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
		++i;
	if (!i)
		return (CLR_ERROR);
	if (i && !(str[i]))
		return (NO_COLOR);
	if (str[i] == ',' && str[i + 1] == '0' && str[i + 2] == 'x')
	{
		if (ft_strlen(&(str[i + 3])) != 6)
			return (CLR_ERROR);
		str[i] = '\0';
		return (ft_atoi_u16(&(str[i + 3])));
	}
	return (CLR_ERROR);
}

void	ft_color_error_render(t_map *map, char **s_map, char **t, t_pos *pos)
{
	if (pos->src_color == CLR_ERROR)
	{
		ft_free_string_arr(t);
		ft_free_string_arr(s_map);
		ft_bad_int_map(pos->y, map);
	}
}

int		ft_get_height(char *map)
{
	int	height;

	height = 0;
	while (*map)
		if (*(map++) == '\n')
			++height;
	return (height);
}

int		ft_allowed_char(char c)
{
	if ((c >= '0' && c <= '9') ||
		(c >= 'A' && c <= 'F') ||
		c == 'x' || c == ',' || c == '-')
		return (1);
	return (0);
}
