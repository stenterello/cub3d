/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:28:36 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/01 22:55:30 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_view(float xy[2], float xy2[2], t_image *view, int x, t_rules *rules)
{
	double	line_height;
	double	dist;
	int		y1;
	int		y2;
	int		x2;

	dist = final_length(xy[0], xy[1], xy2);
	line_height = rules->map.block_width * rules->mlx.win_height / dist;
	y1 = rules->mlx.win_height / 2 - line_height / 2;
	y2 = line_height + y1;
	if (y1 < 0)
		y1 = 0;
	if (y2 > rules->mlx.win_height)
		y2 = rules->mlx.win_height;
	x2 = x + rules->mlx.win_width / 200;
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
