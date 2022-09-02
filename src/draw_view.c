/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:28:36 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 17:42:50 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	phi(t_rules *rules, t_bres_data d)
{
	float	angle_diff;
	double	dist;

	dist = final_length(d.xy[0], d.xy[1], d.xy2);
	if (!dist)
		dist = 1;
	angle_diff = rules->player.dir - d.dir1;
	if (angle_diff < 0)
		angle_diff += (float)(2 * M_PI);
	else if (angle_diff > (float)(2 * M_PI))
		angle_diff -= 2 * M_PI;
	dist *= cos(angle_diff);
	return (dist);
}

void	adjust_var(int var[3], t_rules *rules)
{
	if (var[0] < 0)
		var[0] = 0;
	if (var[1] > rules->mlx.win_height)
		var[1] = rules->mlx.win_height;
	if (var[2] > rules->mlx.win_width)
		var[2] = rules->mlx.win_width;
}

void	draw_view(t_bres_data d, t_image *view, t_rules *rules)
{
	double	line_height;
	double	dist;
	int		var[3];

	dist = phi(rules, d);
	line_height = rules->map.block_width * rules->mlx.win_height / dist;
	var[0] = rules->mlx.win_height / 2 - line_height / 2;
	var[1] = line_height + var[0];
	var[2] = d.x + (rules->mlx.win_width / 725 + 1);
	adjust_var(var, rules);
	while (d.x < var[2])
	{
		var[0] = rules->mlx.win_height / 2 - line_height / 2;
		if (var[0] < 0)
			var[0] = 0;
		else if (var[0] > rules->mlx.win_height)
			var[0] = rules->mlx.win_height;
		while (var[0] < var[1])
			easy_pxl(view, d.x, var[0]++, 0x000000FF);
		d.x++;
	}
}
