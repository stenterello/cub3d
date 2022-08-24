/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:52:18 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 13:03:23 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_plus(char *s1, char *s2)
{
	int		i;
	int		i2;
	char	*ret;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	i2 = 0;
	while (s2[i2])
		ret[i++] = s2[i2++];
	ret[i] = '\0';
	free(s1);
	return (ret);
}
