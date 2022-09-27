/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:08:38 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/23 13:51:47 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

double	our_modulo(double x, double y)
{
	while (x >= y && y != 0)
	{
		x -= y;
	}
	return (x);
}

int	choose_x(t_draw_info *info, float ref, t_rules *rules)
{
	return (our_modulo(ref, rules->map.block_width) * info->tex->width
		/ rules->map.block_width);
}

int	choose_y(int var, t_draw_info *info)
{
	return ((var - info->off) * info->tex->width / info->l_h);
}

unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules)
{
	if (!(x < 0 || x > rules->mlx.win_width - 1
			|| y < 0 || y > rules->mlx.win_height - 1))
	{
		return (*(unsigned int *)(tex->addr + (4 * (tex->width * y + x))));
	}
	return (0x0);
}

void	shoot(t_rules *rules)
{
	ft_strlcpy(rules->player.gun.path, "./img/sparo.xpm", 16);
	rules->player.gun.last_shoot = rules->n_frames;
}
