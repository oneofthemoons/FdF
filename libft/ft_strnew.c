/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:39:20 by lbrown-b          #+#    #+#             */
/*   Updated: 2018/12/10 19:40:09 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	len;

	if (!(str = ft_memalloc(size + 1)))
		return (NULL);
	len = 0;
	while (len < size)
		str[len++] = '\0';
	return (str);
}
