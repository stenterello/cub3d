/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:22:22 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/22 19:54:12 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	final_length(float start_x, float start_y, float rxy[2])
{
	if (rxy[0] == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(get_abs(start_x - rxy[0]), 2) + pow(start_y - rxy[1], 2)));
}

// attualmente casta solo un raggio con una lunghezza prefissata,
// non va a cercare la collisione con il muro

void	horizontal_lines_check(double angle, float xy[2], t_rules *rules, float ret[2])
{
	t_ray	ray;
	double	aTan;
	float		xyoff[2];
	float		dir;

	ray.angle = angle;
	aTan = 1 / tan(ray.angle);
	dir = 0;
	if (ray.angle == 0 || ray.angle == (double)PI)
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
	}
	else if (ray.angle < PI)
	{
		ray.y = xy[1] - (rules->block_width - (rules->block_width - ((int)xy[1] % rules->block_width)));
		ray.x = (xy[1] - ray.y) * aTan + xy[0];
		xyoff[1] = -rules->block_width;
		xyoff[0] = -xyoff[1] * aTan;
	}
	else if (ray.angle > PI)
	{
		ray.y = xy[1] + (rules->block_width - ((int)xy[1] % rules->block_width));
		ray.x = (xy[1] - ray.y) * aTan + xy[0] + 2;
		xyoff[1] = rules->block_width;
		xyoff[0] = -xyoff[1] * aTan;
		dir = 1;
	}
	while (!virtual_horizontal_colliding(ray.x, ray.y, rules, dir) && ray.angle != 0 && ray.angle != (double)PI && ray.x != INT_MAX)
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

void	vertical_lines_check(double angle, float xy[2], t_rules *rules, float ret[2])
{
	t_ray	ray;
	double	nTan;
	float		xyoff[2];
	float		dir;

	ray.angle = angle;
	nTan = -tan(ray.angle);
	dir = 0;
	if (ray.angle == (double)PI / 2 || ray.angle == (double)(3 * PI / 2))
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
	}
	else if (ray.angle < PI / 2 || ray.angle > 3 * PI / 2)
	{
		ray.x = xy[0] + (rules->block_width - ((int)xy[0] % rules->block_width));
		ray.y = xy[1] - (xy[0] - ray.x) * nTan;
		xyoff[0] = rules->block_width;
		xyoff[1] = xyoff[0] * nTan;
	}
	else if (ray.angle > PI / 2 || ray.angle < 3 * PI / 2)
	{
		ray.x = xy[0] - ((int)xy[0] % rules->block_width);
		ray.y = xy[1] - (xy[0] - ray.x) * nTan;
		xyoff[0] = -rules->block_width;
		xyoff[1] = xyoff[0] * nTan;
		dir = 1;
	}
	while (!virtual_vertical_colliding(ray.x, ray.y, rules, dir) && ray.angle != (double)PI / 2 && ray.angle != (double)(3 * PI / 2) && ray.x != INT_MAX)
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

int	mini_virtual_horizontal_colliding(float rayX, float rayY, t_rules *rules, int dir)
{
	int	mapX;
	int	mapY;

	mapX = rayX / rules->mini_block_width;
	if (!dir)
		mapY = rayY / rules->mini_block_width - 1;
	else
		mapY = rayY / rules->mini_block_width;
	if (mapX < 0 || mapY < 0 || mapX > rules->map_width || mapY > rules->map_height)
		return (1);
	if (rules->map[mapY][mapX] == '1')
		return (1);
	return (0);
}

int	mini_virtual_vertical_colliding(int rayX, int rayY, t_rules *rules, int dir)
{
	int	mapX;
	int	mapY;

	if (!dir)
		mapX = rayX / rules->mini_block_width;
	else
		mapX = rayX / rules->mini_block_width - 1;
	mapY = rayY / rules->mini_block_width;
	if (mapX < 0 || mapY < 0 || mapX > rules->map_width - 1 || mapY > rules->map_height - 1)
		return (1);
	if (rules->map[mapY][mapX] == '1')
		return (1);
	return (0);
}

void	mini_horizontal_lines_check(double angle, float xy[2], t_rules *rules, float ret[2])
{
	t_ray	ray;
	double	aTan;
	float		xyoff[2];
	int		dir;

	ray.angle = angle;
	aTan = 1 / tan(ray.angle);
	dir = 0;
	if (ray.angle == 0 || ray.angle == (double)PI)
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
	}
	else if (ray.angle < PI)
	{
		ray.y = xy[1] - (rules->mini_block_width - (rules->mini_block_width - ((int)xy[1] % rules->mini_block_width)));
		ray.x = (xy[1] - ray.y) * aTan + xy[0];
		xyoff[1] = -rules->mini_block_width;
		xyoff[0] = -xyoff[1] * aTan;
	}
	else if (ray.angle > PI)
	{
		ray.y = xy[1] + (rules->mini_block_width - ((int)xy[1] % rules->mini_block_width));
		ray.x = (xy[1] - ray.y) * aTan + xy[0] + 2; // QUESTO + 1 E' MESSO A CAZZO MA PARE FUNZIONARE COSI'
		xyoff[1] = rules->mini_block_width;
		xyoff[0] = -xyoff[1] * aTan;
		dir = 1;
	}
	while (!mini_virtual_horizontal_colliding(ray.x, ray.y, rules, dir) && ray.angle != 0 && ray.angle != (double)PI && ray.x != INT_MAX)
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

void	mini_vertical_lines_check(double angle, float xy[2], t_rules *rules, float ret[2])
{
	t_ray	ray;
	double	nTan;
	float		xyoff[2];
	float		dir;

	ray.angle = angle;
	nTan = -tan(ray.angle);
	dir = 0;
	if (ray.angle == (double)PI / 2 || ray.angle == (double)(3 * PI / 2))
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
	}
	else if (ray.angle < PI / 2 || ray.angle > 3 * PI / 2)
	{
		ray.x = xy[0] + (rules->mini_block_width - ((int)xy[0] % rules->mini_block_width));
		ray.y = xy[1] - (xy[0] - ray.x) * nTan;
		xyoff[0] = rules->mini_block_width;
		xyoff[1] = xyoff[0] * nTan;
	}
	else if (ray.angle > PI / 2 && ray.angle < 3 * PI / 2)
	{
		ray.x = xy[0] - ((int)xy[0] % rules->mini_block_width);
		ray.y = xy[1] - (xy[0] - ray.x) * nTan;
		xyoff[0] = -rules->mini_block_width;
		xyoff[1] = xyoff[0] * nTan;
		dir = 1;
	}
	while (!mini_virtual_vertical_colliding(ray.x, ray.y, rules, dir) && ray.angle != (double)PI / 2 && ray.angle != (double)(3 * PI / 2) && ray.x != INT_MAX)
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

void	mini_raycast(double angle, t_rules *rules)
{
	float		xy[2];
	float		f_pts[2];
	float		s_pts[2];

	xy[0] = rules->player.miniplayer.x;
	xy[1] = rules->player.miniplayer.y;
	mini_horizontal_lines_check(angle, xy, rules, f_pts);
	mini_vertical_lines_check(angle, xy, rules, s_pts);
	if (final_length(xy[0], xy[1], s_pts) == INT_MAX || final_length(xy[0], xy[1], f_pts) < final_length(xy[0], xy[1], s_pts))
	{
		bresenham(xy, f_pts, 0x00FFFFFF, rules);
		// draw_3d(rules, final_length(xy[0], xy[1], f_pts), counter, angle);
	}
	else
	{
		bresenham(xy, s_pts, 0x00FFFFFF, rules);
		// draw_3d(rules, final_length(xy[0], xy[1], s_pts), counter, angle);
	}
}

void	raycast_bresenham(double angle, t_rules *rules, int counter, t_frame *scene)
{
	float		xy[2];
	float		f_pts[2];
	float		s_pts[2];
	float		angle_diff;
	double		dist;
	int			color_unit_x;

	
	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	angle_diff = rules->player.dir - angle;
	if (angle_diff < 0)
		angle_diff += (float)(2 * PI);
	else if (angle_diff > (float)(2 * PI))
		angle_diff -= 2 * PI;
	horizontal_lines_check(angle, xy, rules, f_pts);
	vertical_lines_check(angle, xy, rules, s_pts);
	if (final_length(xy[0], xy[1], s_pts) == INT_MAX || final_length(xy[0], xy[1], f_pts) < final_length(xy[0], xy[1], s_pts))
		dist = final_length(xy[0], xy[1], f_pts);
	else
		dist = final_length(xy[0], xy[1], s_pts);
	dist *= cos(angle_diff);
	color_unit_x = counter / round((rules->block_width * rules->win_height / dist) / rules->north_texture.size[0]);
	if (color_unit_x >= rules->north_texture.size[0])
		color_unit_x %= rules->north_texture.size[0];
	draw_texture(counter, dist, rules, scene, color_unit_x);
}
