/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 21:55:43 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 14:19:46 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_line_width(t_rules *rules)
{
	int		ret;
	double	start;

	ret = 0;
	start = decrement_angle(rules->player.dir, 45);
	while (start != increment_angle(rules->player.dir, 45))
	{
		start += ANGLE_UNIT;
		if (start > 2 * PI)
			start = 0;
		ret++;
	}
	return (rules->win_width / ret + 1);
}

void	draw_3d(t_rules *rules, double dist, int *x, double ray_angle)//, int color)
{
	float	line_height;
	float	line_off;
	// int		i;
	int		xy[2];
	int		xy2[2];
	float	angle_diff;

	angle_diff = rules->player.dir - ray_angle;
	if (angle_diff < 0)
		angle_diff += (float)(2 * PI);
	else if (angle_diff > (float)(2 * PI))
		angle_diff -= 2 * PI;
	dist *= cos(angle_diff);
	line_height = rules->block_width * rules->win_height / dist;
	line_off = rules->win_height / 2 - line_height / 2;
	xy[0] = *x;
	xy[1] = line_off;
	xy2[0] = *x;
	xy2[1] = line_height + line_off;
	// i = 0;
	//bresenham(xy, xy2, color, rules);
	draw_texture(xy, xy2, rules, line_height);
	xy[0] += get_line_width(rules);
	xy2[0] += get_line_width(rules);
	(*x) += get_line_width(rules);
}
