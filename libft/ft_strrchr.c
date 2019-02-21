/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:49:03 by lbrown-b          #+#    #+#             */
/*   Updated: 2018/12/07 19:42:50 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = (char*)s;
	while (tmp[len] != '\0')
		len++;
	while (len >= 0)
	{
		if (tmp[len] == ((char)c))
			return (&tmp[len]);
		len--;
	}
	return (NULL);
}
