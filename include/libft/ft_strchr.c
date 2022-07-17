/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:37:50 by ddelladi          #+#    #+#             */
/*   Updated: 2022/01/11 17:27:40 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (*(s + i) == (char) c)
		return ((char *) &s[i]);
	else
		return (NULL);
}
