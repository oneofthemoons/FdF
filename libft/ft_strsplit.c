/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrown-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:14:59 by lbrown-b          #+#    #+#             */
/*   Updated: 2018/12/10 20:43:55 by lbrown-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_mal_clean(char ***str)
{
	while (*str)
	{
		free(str);
		str++;
	}
	free(*str);
}

static char		*ft_write_word(int word_len, char const *start)
{
	int		len;
	char	*str;

	len = 0;
	if (!(str = (char*)malloc(sizeof(char) * (word_len + 1))))
		return (NULL);
	while (len < word_len)
	{
		str[len] = *start;
		len++;
		start++;
	}
	str[len] = '\0';
	return (str);
}

static int		ft_len(char const *s, char c)
{
	int len;

	len = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			len++;
		s++;
	}
	return (len);
}

static int		ft_word_len(char const *s, char c)
{
	int word_len;

	word_len = 0;
	while (*s != c && *s)
	{
		word_len++;
		s++;
	}
	return (word_len);
}

char			**ft_strsplit(char const *s, char c)
{
	int			word_len;
	char		**str;
	int			j;

	if (s && (str = (char**)malloc(sizeof(char*) * (ft_len(&(*s), c) + 1))))
	{
		j = 0;
		while (*s)
		{
			if (*s != c)
			{
				word_len = ft_word_len(s, c);
				if (word_len > 0)
				{
					if (!(str[j++] = ft_write_word(word_len, s)))
						ft_mal_clean(&str);
					s += word_len - 1;
				}
			}
			s++;
		}
		str[j++] = NULL;
		return (str);
	}
	return (NULL);
}
