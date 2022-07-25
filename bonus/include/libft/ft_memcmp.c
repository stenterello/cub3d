/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:45:57 by ddelladi          #+#    #+#             */
/*   Updated: 2022/01/11 18:17:05 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*f;
	unsigned char	*s;
	size_t			i;

	f = (unsigned char *) s1;
	s = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (*(f + i) != *(s + i))
			return (*(f + i) - *(s + i));
		i++;
	}
	return (0);
}
