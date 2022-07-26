/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:15:51 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 15:01:05 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_pair(char **str, t_texture *texture)
{
	char	tmp[2];
	t_xpm	*ptr;

	if (!*str)
		return (NULL);
	tmp[0] = str[0][0];
	tmp[1] = str[0][1];
	ptr = texture->pairs;
	while (ptr)
	{
		if (ft_strlen(texture->delimiters) > 1)
		{
			if (!ft_strncmp((char *)ptr->key, tmp, ft_strlen(ptr->key)))
				return (ptr->value);
		}
		else
		{
			if (!ft_strncmp((char *)ptr->key, tmp, 1))
				return (ptr->value);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

int	get_xpm_color(t_texture *texture, int y, int x)
{
	return (get_nbr_hex(get_pair(&texture->encoded
				[y % texture->size[0]][x % texture->size[0]], texture)));
}

void	draw_ceiling(int x, int y1, t_frame *scene, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < y1)
		easy_pixel_put(scene, x, i++,
			mlx_get_color_value(rules->mlx.mlx,
				get_hex_color(rules->ceiling_color)));
}

void	draw_floor(int x, int y1, t_frame *scene, t_rules *rules)
{
	while (y1 < rules->mlx.win_height)
		easy_pixel_put(scene, x, y1++,
			mlx_get_color_value(rules->mlx.mlx,
				get_hex_color(rules->floor_color)));
}

void	draw_texture(int x, double dist, t_texture_info *info, int color_unit_x)
{
	double	line_height;
	float	y2;
	int		y1;
	int		off;

	line_height = info->rules->map.block * info->rules->mlx.win_height / dist;
	y1 = info->rules->mlx.win_height / 2 - line_height / 2;
	y2 = line_height + y1;
	if (y1 < 0)
		y1 = 0;
	if (y2 > info->rules->mlx.win_height)
		y2 = info->rules->mlx.win_height;
	draw_ceiling(x, y1, info->scene, info->rules);
	off = y1;
	while (y1 < y2)
	{
		easy_pixel_put(info->scene, x, y1,
			get_xpm_color(info->texture,
				(y1 - off) * info->texture->size[0]
				/ line_height, color_unit_x));
		y1++;
	}
	draw_floor(x, y1, info->scene, info->rules);
}
