/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:28:36 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 17:06:03 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_view(float xy[2], float xy2[2], t_image *view, int x, t_rules *rules, double dir1)
{
	double	line_height;
	double	dist;
	int		y1;
	int		y2;
	int		x2;
	float	angle_diff;

	dist = final_length(xy[0], xy[1], xy2);
	if (!dist)
		dist = 1;
	angle_diff = rules->player.dir - dir1;
	if (angle_diff < 0)
		angle_diff += (float)(2 * M_PI);
	else if (angle_diff > (float)(2 * M_PI))
		angle_diff -= 2 * M_PI;
	dist *= cos(angle_diff);
	line_height = rules->map.block_width * rules->mlx.win_height / dist;
	y1 = rules->mlx.win_height / 2 - line_height / 2;
	y2 = line_height + y1;
	if (y1 < 0)
		y1 = 0;
	if (y2 > rules->mlx.win_height)
		y2 = rules->mlx.win_height;
	x2 = x + (rules->mlx.win_width / 725 + 1);
	if (x2 > rules->mlx.win_width)
		x2 = rules->mlx.win_width;
	while (x < x2)
	{
		y1 = rules->mlx.win_height / 2 - line_height / 2;
		if (y1 < 0)
			y1 = 0;
		else if (y1 > rules->mlx.win_height)
			y1 = rules->mlx.win_height;
		while (y1 < y2)
			my_mlx_pixel_put(view, x, y1++, 0x000000FF);
		x++;
	}
}
