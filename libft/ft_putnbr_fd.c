/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:57:36 by lbrown-b          #+#    #+#             */
/*   Updated: 2018/12/07 19:17:55 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 2147483647 || n > -2147483648)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			if (n == -2147483648)
			{
				n = -214748364;
				ft_putnbr_fd(-n, fd);
				ft_putnbr_fd(8, fd);
			}
			else
				ft_putnbr_fd(-n, fd);
		}
		else if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd(n % 10 + '0', fd);
		}
		else
			ft_putchar_fd(n + '0', fd);
	}
}
