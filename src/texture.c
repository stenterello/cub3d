/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:15:51 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 22:13:01 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_pair(char *str, t_texture *texture)
{
	char	tmp[2];
	t_xpm	*ptr;

	tmp[0] = str[0];
	tmp[1] = str[1];
	ptr = texture->pairs;
	while (ptr)
	{
		if (!ft_strncmp((char *)ptr->key, tmp, 1))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

int	get_xpm_color(t_texture *texture, int y, int x)
{
	return (get_nbr_hex(get_pair(&texture->encoded[y % 32][x * 2 % 32], texture)));
}

void	draw_texture(int x, int y1, int y2, t_rules *rules, t_frame *scene)
{
	int		i;

	i = 0;
	if (y1 < 0)
		y1 = 0;
	if (y2 > rules->win_height)
		y2 = rules->win_height;
	while (y1 < y2)
	{
		easy_pixel_put(scene, x, y1++, get_xpm_color(&rules->north_texture, i, x));
		i++;
		if (i >= rules->north_texture.size[0])
			i = 0;
	}
}
