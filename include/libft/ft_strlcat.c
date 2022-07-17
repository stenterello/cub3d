/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:56:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/05/24 16:59:08 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_return(size_t d, char *dst, char *src, unsigned int sum)
{
	size_t	a;
	size_t	b;

	a = ft_strlen((const char *)dst);
	b = ft_strlen((const char *)src);
	sum = a + b;
	if (a < d)
		return (sum);
	else
		return (b + d);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	size_t			i2;
	unsigned int	sum;

	i = ft_strlen((const char *)dst);
	sum = 0;
	sum = check_return(dstsize, dst, (char *)src, sum);
	i2 = 0;
	if (dstsize > 0 && ft_strlen(dst) <= dstsize)
	{
		while (*(char *)(src + i2) != '\0' && i < dstsize - 1)
		{
			*(dst + i) = (char)*(src + i2);
			i2++;
			i++;
		}
		*(dst + i) = '\0';
	}
	return (sum);
}
