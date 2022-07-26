/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:32:53 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 14:42:05 by ddelladi         ###   ########.fr       */
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

void	define_paint(t_rules *rules, float pts[3],
	double angle, t_frame *scene)
{
	double			dist;
	t_texture		*chosen;
	int				color_unit_x;
	t_texture_info	*info;

	dist = final_length(rules->player.x, rules->player.y, pts);
	chosen = &rules->textures[choose_texture(pts[2], 0)];
	color_unit_x = chosen->size[0] * round(((int)pts[0]
				% rules->map.block)) / rules->map.block;
	define_dist(&dist, angle, rules);
	info = malloc(sizeof(t_texture_info));
	if (!info)
		die("Malloc error");
	info->rules = rules;
	info->scene = scene;
	info->texture = chosen;
	draw_texture(rules->counter, dist, info, color_unit_x);
	free(info);
}
