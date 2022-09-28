/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:41:24 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/28 21:38:56 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_sprites(t_rules *rules, t_image *view)
{
	t_sprite	dot;
	float		x;
	float		y;
	float		z;
	float		a;
	float		b;

	dot.x = 1.5 * 64;
	dot.y = 5 * 64;
	dot.z = 0;
	x = dot.x - rules->player.x;
	y = dot.y - rules->player.y;
	z = dot.z;
	a = y * cos(rules->player.dir) + x * sin(rules->player.dir);
	b = x * cos(rules->player.dir) - y * sin(rules->player.dir);
	x = a;
	y = b;

	x = (x * 108.0 / y) + (rules->mlx.win_width / 2);
	y = (dot.z * 108.0 / y) + (rules->map.block_width / 2);

	int	i;
	int	i2;

	i = -1;
	while (++i < 6)
	{
		i2 = -1;
		int y2 = y;
		while (i2++ < 6)
			easy_pxl(view, x, y2++, 0x00FFFF00);
		x++;
	}
	(void)x;
(void)y;
(void)z;
	(void)view;
}
