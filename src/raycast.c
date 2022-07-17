/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:22:22 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/18 00:30:57 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	final_length(int start_x, int start_y, int rxy[2])
{
	if (rxy[0] == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(get_abs(start_x - rxy[0]), 2) + pow(start_y - rxy[1], 2)));
}

// attualmente casta solo un raggio con una lunghezza prefissata,
// non va a cercare la collisione con il muro

void	horizontal_lines_check(float angle, int xy[2], t_rules *rules, int ret[2])
{
	t_ray	ray;
	float	aTan;
	int		xyoff[2];
	int		dir;

	ray.angle = angle;
	aTan = -1 / tan(ray.angle);
	dir = 0;
	if (ray.angle == 0 || ray.angle == (float)PI)
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
	}
	else if (ray.angle > PI)
	{
		ray.y = xy[1] + (rules->mini_block_width - (xy[1] % rules->mini_block_width));
		ray.x = (xy[1] - ray.y) * aTan + xy[0];
		xyoff[1] = rules->mini_block_width;
		xyoff[0] = -xyoff[1] * aTan;
		dir = 1;
	}
	else if (ray.angle < PI)
	{
		ray.y = xy[1] - (xy[1] % rules->mini_block_width);
		ray.x = (xy[1] - ray.y) * aTan + xy[0];
		xyoff[1] = -rules->mini_block_width;
		xyoff[0] = -xyoff[1] * aTan;
	}
	while (!virtual_horizontal_colliding(ray.x, ray.y, rules, dir) && ray.angle != 0 && ray.angle != (float)PI && ray.x != INT_MAX)
	{
		ray.x += xyoff[0];
		ray.y += xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
	// disegna questa linea qui sotto per fare il check del calcolo
	// if (ray.x != INT_MAX)
	// 	bresenham(xy, ret, 0x00FFFFFF, rules);
}

void	vertical_lines_check(float angle, int xy[2], t_rules *rules, int ret[2])
{
	t_ray	ray;
	float	nTan;
	int		xyoff[2];
	int		dir;

	ray.angle = angle;
	nTan = -tan(ray.angle);
	dir = 0;
	if (ray.angle == (float)PI / 2 || ray.angle == (float)(3 * PI / 2))
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
	}
	else if (ray.angle > PI / 2 && ray.angle < 3 * PI / 2)
	{
		ray.x = xy[0] + (rules->mini_block_width - (xy[0] % rules->mini_block_width));
		ray.y = (xy[0] - ray.x) * nTan + xy[1];
		xyoff[0] = rules->mini_block_width;
		xyoff[1] = -xyoff[0] * nTan;
	}
	else if (ray.angle < PI / 2 || ray.angle > 3 * PI / 2)
	{
		ray.x = xy[0] - (xy[0] % rules->mini_block_width);
		ray.y = (xy[0] - ray.x) * nTan + xy[1];
		xyoff[0] = -rules->mini_block_width;
		xyoff[1] = -xyoff[0] * nTan;
		dir = 1;
	}
	while (!virtual_vertical_colliding(ray.x, ray.y, rules, dir) && ray.angle != (float)PI / 2 && ray.angle != (float)(3 * PI / 2) && ray.x != INT_MAX)
	{
		ray.x += xyoff[0];
		ray.y += xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
	// disegna questa linea qui sotto per fare il check del calcolo
	// if (ray.x != INT_MAX)
	// 	bresenham(xy, ret, 0x00000000, rules);
}

void	raycast_bresenham(float angle, t_rules *rules, int counter)
{
	int		xy[2];
	int		f_pts[2];
	int		s_pts[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	horizontal_lines_check(angle, xy, rules, f_pts);
	vertical_lines_check(angle, xy, rules, s_pts);
	if (final_length(xy[0], xy[1], s_pts) == INT_MAX || final_length(xy[0], xy[1], f_pts) < final_length(xy[0], xy[1], s_pts))
	{
		bresenham(xy, f_pts, 0x00FFFFFF, rules);
		draw_3d(rules, final_length(xy[0], xy[1], f_pts), counter, angle);
	}
	else
	{
		bresenham(xy, s_pts, 0x00FFFFFF, rules);
		draw_3d(rules, final_length(xy[0], xy[1], s_pts), counter, angle);
	}
}
