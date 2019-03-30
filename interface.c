/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrickard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:47:45 by hrickard          #+#    #+#             */
/*   Updated: 2019/03/30 15:47:46 by hrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_str_instuct(t_fdf *fdf, char *str, int line)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20,
		WIN_HEIGHT - (260 - line * 20), 0xFFFAFA, str);
}

void	ft_instruction(t_fdf *fdf)
{
	ft_str_instuct(fdf, "Press:", 0);
	ft_str_instuct(fdf, "ESC to exit", 2);
	ft_str_instuct(fdf, "F to pay respect", 3);
	ft_str_instuct(fdf, "ARROW UP to zoom+", 4);
	ft_str_instuct(fdf, "ARROW DOWN to zoom-", 5);
	ft_str_instuct(fdf, "I to choose ISO projection", 6);
	ft_str_instuct(fdf, "P to choose PARALLEL projection", 7);
	ft_str_instuct(fdf, "W/S to rotate in X axis (PARALLEL)", 8);
	ft_str_instuct(fdf, "D/A to rotate in Z axis (PARALLEL)", 9);
	ft_str_instuct(fdf, "Q/E to rotate in Y axis (PARALLEL)", 10);
	ft_str_instuct(fdf, "R to reset rotation in PARALLEL projection", 11);
}

int		ft_close(void *fdf)
{
	int	i;

	i = -1;
	while (++i < ((t_fdf*)fdf)->s_map.height)
	{
		free(((t_fdf*)fdf)->c_map.points[i]);
		free(((t_fdf*)fdf)->h_map.points[i]);
		free(((t_fdf*)fdf)->s_map.points[i]);
	}
	free(((t_fdf*)fdf)->c_map.points);
	free(((t_fdf*)fdf)->s_map.points);
	free(((t_fdf*)fdf)->h_map.points);
	mlx_destroy_image(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->respect.ptr);
	mlx_destroy_image(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->img.ptr);
	mlx_destroy_window(((t_fdf*)fdf)->mlx_ptr, ((t_fdf*)fdf)->win_ptr);
	exit(0);
	return (0);
}
