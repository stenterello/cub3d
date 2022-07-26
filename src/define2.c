/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:32:53 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 15:33:24 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	define_dist(double *dist, double angle, t_rules *rules)
{
	float	angle_diff;

	angle_diff = rules->player.dir - angle;
	if (angle_diff < 0)
		angle_diff += (float)(2 * PI);
	else if (angle_diff > (float)(2 * PI))
		angle_diff -= 2 * PI;
	*dist *= cos(angle_diff);
}

void	define_paint(t_texture_info *info, float pts[3],
	double angle)
{
	double			dist;
	t_texture		*chosen;
	int				color_unit_x;

	dist = final_length(info->rules->player.x, info->rules->player.y, pts);
	chosen = &info->rules->textures[choose_texture(pts[2], info->flag)];
	if (!info->flag)
		color_unit_x = chosen->size[0] * round(((int)pts[0]
				% info->rules->map.block)) / info->rules->map.block;
	else
		color_unit_x = chosen->size[0] * round(((int)pts[1]
				% info->rules->map.block)) / info->rules->map.block;
	define_dist(&dist, angle, info->rules);
	info->texture = chosen;
	draw_texture(info->rules->counter, dist, info, color_unit_x);
	free(info);
}
