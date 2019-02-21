/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:02:38 by lbrown-b          #+#    #+#             */
/*   Updated: 2018/12/10 19:37:19 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_nbr(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

static void	ft_putnb(char *str, int n, int len)
{
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
}

char		*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	len = ft_len_nbr(n);
	if (!(str = (char*)malloc(sizeof(char) * (len))))
		return (NULL);
	else if (n < 0)
	{
		n = n * -1;
		len--;
		ft_putnb(str, n, len);
		str[0] = '-';
	}
	else
	{
		len--;
		ft_putnb(str, n, len);
	}
	return (str);
}
