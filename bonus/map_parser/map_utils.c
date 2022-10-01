/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:41:34 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/01 12:53:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_measures(int fd, int hl[2])
{
	char	*tmp;

	hl[0] = 0;
	hl[1] = 1;
	tmp = get_next_line(fd);
	while (tmp)
	{
		if ((int)ft_strlen(tmp) > hl[0])
			hl[0] = ft_strlen(tmp);
		hl[1]++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
}
