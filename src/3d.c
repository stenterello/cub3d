/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 21:55:43 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/20 11:42:34 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_line_width(t_rules *rules)
{
	int		ret;
	double	start;

	ret = 0;
	start = rules->player.dir - (ANGLE_UNIT * 45);
	while (start < rules->player.dir + (ANGLE_UNIT * 45))
	{
		start += ANGLE_UNIT / 4;
		ret++;
	}
	return (rules->win_width / ret);
}

void	draw_3d(t_rules *rules, float dist, int *x, double ray_angle)
{
	float	line_height;
	float	line_off;
	int		i;
	int		xy[2];
	int		xy2[2];
	float	angle_diff;

	angle_diff = rules->player.dir - ray_angle;
	if (angle_diff < 0)
		angle_diff += (float)(2 * PI);
	else if (angle_diff > (float)(2 * PI))
		angle_diff -= 2 * PI;
	dist *= cos(angle_diff);
	line_height = rules->mini_block_width * rules->win_height / dist;
	line_off = rules->win_height / 2 - line_height / 2;
	xy[0] = *x;
	xy[1] = line_off;
	xy2[0] = *x;
	xy2[1] = line_height + line_off;
	i = 0;
	while (i++ <= get_line_width(rules))
	{
		bresenham(xy, xy2, 0x000000FF, rules);
		xy[0]++;
		xy2[0]++;
		(*x)++;
	}
}
