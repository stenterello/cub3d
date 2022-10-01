/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:08:54 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 15:23:52 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules)
{
	if (!(x < 0 || x > rules->mlx.win_width - 1
			|| y < 0 || y > rules->mlx.win_height - 1))
	{
		return (*(unsigned int *)(tex->addr + (4 * (tex->width * y + x))));
	}
	return (0x0);
}

unsigned int	get_color_arr(unsigned char arr[3])
{
	return (*(unsigned int *)(unsigned char [4]){arr[2], arr[1], arr[0], 0});
}

unsigned int	get_sprite_color(t_image *tex, int x, int y, t_rules *rules)
{
	if ((x > 0 || x < rules->mlx.win_width
			|| y > 0 || y < rules->mlx.win_height) 
			&& *(unsigned int *)(tex->addr + (4 * (tex->width * y + x))))
	{
		return (*(unsigned int *)(tex->addr + (4 * (tex->width * y + x))));
	}
	return (0x0);
}
