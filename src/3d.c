/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 21:55:43 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/17 22:32:23 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_rules *rules, int dist, int x, float ray_angle)
{
	float	line_height;
	float	line_off;
	int		i;
	int		xy[2];
	int		xy2[2];
	float	angle_diff;

	angle_diff = rules->player.dir - ray_angle;
	if (angle_diff < 0)
		angle_diff += 2 * PI;
	else if (angle_diff > 2 * PI)
		angle_diff -= 2 * PI;
	dist *= cos(angle_diff);
	line_height = rules->mini_block_width * rules->win_height / dist;
	line_off = 500 - line_height / 2;
	xy[0] = x + rules->win_width / 3;
	xy[1] = line_off;
	xy2[0] = x + rules->win_width / 3;
	xy2[1] = line_height + line_off;
	i = 0;
	while (i++ < 12)
	{
		bresenham(xy, xy2, 0x000000FF, rules);
		xy[0]++;
		xy2[0]++;
	}
}
