/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:15:51 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 14:19:39 by ddelladi         ###   ########.fr       */
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

void	draw_texture(int xy[2], int xy2[2], t_rules *rules, float line_height)
{
	int		i;
	int		i2;
	int		i3;
	int		i4;
	t_frame	img;

	img.img = mlx_new_image(rules->mlx, get_line_width(rules), line_height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	i = xy[1];
	i2 = 0;
	i3 = rules->north_texture.last_x;
	if (i3 >= rules->north_texture.size[0])
		i3 %= rules->north_texture.size[0];
	i4 = i3;
	while (i < xy2[1])
	{
		i3 = i4;
		while (++i3 - i4 < get_line_width(rules))
		{
			easy_pixel_put(&img, i3, i2, get_xpm_color(&rules->north_texture, i2, i3));
		}
		i++;
		i2++;
	}
	rules->north_texture.last_x = i3;
	mlx_put_image_to_window(rules->mlx, rules->mlx_win, img.img, xy[0], xy[1]);
}
