/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:50:25 by ddelladi          #+#    #+#             */
/*   Updated: 2022/01/19 16:36:15 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		i2;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	i2 = ft_strlen(s2);
	ret = malloc(sizeof(char) * (i + i2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (*(s1 + i) != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	ft_strlcpy(&ret[i], s2, i2 + 1);
	return (ret);
}
