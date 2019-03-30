/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:01:10 by hrickard          #+#    #+#             */
/*   Updated: 2019/03/30 17:01:14 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_bad_map(int fd, char *c_map)
{
	free(c_map);
	close(fd);
	ft_print_error("error: bad map\n");
}

void	ft_bad_int_map(int height, t_map *map)
{
	while (height--)
		free(map->points[height]);
	free(map->points);
	ft_print_error("error: bad map\n");
}
