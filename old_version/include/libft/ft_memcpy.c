/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:37:02 by ddelladi          #+#    #+#             */
/*   Updated: 2022/01/19 14:35:30 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*ret;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	s1 = (unsigned char *) dst;
	s2 = (unsigned char *) src;
	ret = dst;
	i = 0;
	while (i < n)
	{
		*(s1 + i) = *(s2 + i);
		i++;
	}
	return (ret);
}
