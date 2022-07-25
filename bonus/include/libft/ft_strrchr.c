/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:39:42 by ddelladi          #+#    #+#             */
/*   Updated: 2022/01/11 17:30:03 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if ((char)*(s + len) == (char) c)
			return ((char *) &s[len]);
		len--;
	}
	return (NULL);
}
