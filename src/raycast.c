/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:22:22 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 12:24:24 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	final_length(float start_x, float start_y, float rxy[2])
{
	if (rxy[0] == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(get_abs(start_x - rxy[0]), 2) + pow(start_y - rxy[1], 2)));
}

void	horizontal_lines_check(double angle, float xy[2], t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	aTan;
	float	xyoff[2];

	ray.angle = angle;
	aTan = 1 / tan(ray.angle);
	if (ray.angle == 0 || ray.angle == (double)PI)
	{
		ray.x = INT_MAX; // not so secure...
		ray.y = INT_MAX;
		ret[2] = 0;
	}
	else if (ray.angle < PI)
	{
		ray.y = xy[1] - (rules->map.block - (rules->map.block - ((int)xy[1] % rules->map.block)));
		ray.x = (xy[1] - ray.y) * aTan + xy[0];
		xyoff[1] = -rules->map.block;
		xyoff[0] = -xyoff[1] * aTan;
		ret[2] = 0;
	}
	else if (ray.angle > PI)
	{
		ray.y = xy[1] + (rules->map.block - ((int)xy[1] % rules->map.block));
		ray.x = (xy[1] - ray.y) * aTan + xy[0];
		xyoff[1] = rules->map.block;
		xyoff[0] = -xyoff[1] * aTan;
		ret[2] = 1;
	}
	while (!virtual_horizontal_colliding(ray.x, ray.y, rules, ret[2]) && ray.angle != 0 && ray.angle != (double)PI && ray.x != INT_MAX)
	{
		ray.x += xyoff[0];
		ray.y += xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
}

void	vertical_lines_check(double angle, float xy[2], t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	nTan;
	float		xyoff[2];

	ray.angle = angle;
	nTan = -tan(ray.angle);
	if (ray.angle == (double)PI / 2 || ray.angle == (double)(3 * PI / 2))
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
		ret[2] = 0;
	}
	else if (ray.angle < PI / 2 || ray.angle > 3 * PI / 2)
	{
		ray.x = xy[0] + (rules->map.block - ((int)xy[0] % rules->map.block));
		ray.y = xy[1] - (xy[0] - ray.x) * nTan;
		xyoff[0] = rules->map.block;
		xyoff[1] = xyoff[0] * nTan;
		ret[2] = 0;
	}
	else if (ray.angle > PI / 2 || ray.angle < 3 * PI / 2)
	{
		ray.x = xy[0] - ((int)xy[0] % rules->map.block);
		ray.y = xy[1] - (xy[0] - ray.x) * nTan;
		xyoff[0] = -rules->map.block;
		xyoff[1] = xyoff[0] * nTan;
		ret[2] = 1;
	}
	while (!virtual_vertical_colliding(ray.x, ray.y, rules, ret[2]) && ray.angle != (double)PI / 2 && ray.angle != (double)(3 * PI / 2) && ray.x != INT_MAX)
	{
		ray.x += xyoff[0];
		ray.y += xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
}

int	mini_virtual_horizontal_colliding(float rayX, float rayY, t_rules *rules, int dir)
{
	int	mapX;
	int	mapY;

	mapX = (rayX - 2) / rules->map.mini_block;
	if (!dir)
		mapY = rayY / rules->map.mini_block - 1;
	else
		mapY = rayY / rules->map.mini_block;
	if (mapX < 0 || mapY < 0 || mapX > rules->map.map_width || mapY > rules->map.map_height)
		return (1);
	if (rules->map.map[mapY][mapX] == '1')
		return (1);
	return (0);
}

int	mini_virtual_vertical_colliding(int rayX, int rayY, t_rules *rules, int dir)
{
	int	mapX;
	int	mapY;

	if (!dir)
		mapX = rayX / rules->map.mini_block;
	else
		mapX = rayX / rules->map.mini_block - 1;
	mapY = rayY / rules->map.mini_block;
	if (mapX < 0 || mapY < 0 || mapX > rules->map.map_width - 1 || mapY > rules->map.map_height - 1)
		return (1);
	if (rules->map.map[mapY][mapX] == '1')
		return (1);
	return (0);
}

void	mini_horizontal_lines_check(double angle, float xy[2], t_rules *rules, float ret[2])
{
	t_ray	ray;
	double	aTan;
	float	xyoff[2];

	ray.angle = angle;
	aTan = 1 / tan(ray.angle);
	if (ray.angle == 0 || ray.angle == (double)PI)
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
		ret[2] = 0;
	}
	else if (ray.angle < PI)
	{
		ray.y = xy[1] - (rules->map.mini_block - (rules->map.mini_block - ((int)xy[1] % rules->map.mini_block)));
		ray.x = (xy[1] - ray.y) * aTan + xy[0];
		xyoff[1] = -rules->map.mini_block;
		xyoff[0] = -xyoff[1] * aTan;
		ret[2] = 0;
	}
	else if (ray.angle > PI)
	{
		ray.y = xy[1] + (rules->map.mini_block - ((int)xy[1] % rules->map.mini_block));
		ray.x = (xy[1] - ray.y) * aTan + xy[0];
		xyoff[1] = rules->map.mini_block;
		xyoff[0] = -xyoff[1] * aTan;
		ret[2] = 1;
	}
	while (!mini_virtual_horizontal_colliding(ray.x, ray.y, rules, ret[2]) && ray.angle != 0 && ray.angle != (double)PI && ray.x != INT_MAX)
	{
		ray.x += xyoff[0];
		ray.y += xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
}

void	mini_vertical_lines_check(double angle, float xy[2], t_rules *rules, float ret[2])
{
	t_ray	ray;
	double	nTan;
	float	xyoff[2];

	ray.angle = angle;
	nTan = -tan(ray.angle);
	if (ray.angle == (double)PI / 2 || ray.angle == (double)(3 * PI / 2))
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
		ret[2] = 0;
	}
	else if (ray.angle < PI / 2 || ray.angle > 3 * PI / 2)
	{
		ray.x = xy[0] + (rules->map.mini_block - ((int)xy[0] % rules->map.mini_block));
		ray.y = xy[1] - (xy[0] - ray.x) * nTan;
		xyoff[0] = rules->map.mini_block;
		xyoff[1] = xyoff[0] * nTan;
		ret[2] = 0;
	}
	else if (ray.angle > PI / 2 && ray.angle < 3 * PI / 2)
	{
		ray.x = xy[0] - ((int)xy[0] % rules->map.mini_block);
		ray.y = xy[1] - (xy[0] - ray.x) * nTan;
		xyoff[0] = -rules->map.mini_block;
		xyoff[1] = xyoff[0] * nTan;
		ret[2] = 1;
	}
	while (!mini_virtual_vertical_colliding(ray.x, ray.y, rules, ret[2]) && ray.angle != (double)PI / 2 && ray.angle != (double)(3 * PI / 2) && ray.x != INT_MAX)
	{
		ray.x += xyoff[0];
		ray.y += xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
}

void	mini_raycast(double angle, t_rules *rules)
{
	float		xy[2];
	float		f_pts[3];
	float		s_pts[3];

	xy[0] = rules->player.miniplayer.x;
	xy[1] = rules->player.miniplayer.y;
	mini_horizontal_lines_check(angle, xy, rules, f_pts);
	mini_vertical_lines_check(angle, xy, rules, s_pts);
	if (final_length(xy[0], xy[1], s_pts) == INT_MAX || final_length(xy[0], xy[1], f_pts) < final_length(xy[0], xy[1], s_pts))
		bresenham(xy, f_pts, 0x00FFFFFF, rules);
	else
		bresenham(xy, s_pts, 0x00FFFFFF, rules);
}

int	choose_texture(int n, int flag)
{
	if (!flag && !n)
		return (0);
	if (!flag && n)
		return (1);
	if (flag && !n)
		return (2);
	if (flag && n)
		return (3);
	return (0);
}

void	raycast_bresenham(double angle, t_rules *rules, int counter, t_frame *scene)
{
	float		xy[2];
	float		f_pts[3];
	float		s_pts[3];
	float		angle_diff;
	double		dist;
	int			color_unit_x;
	t_texture	*chosen;
	
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
	{
		dist = final_length(xy[0], xy[1], f_pts);
		chosen = &rules->textures[choose_texture(f_pts[2], 0)];
		color_unit_x = rules->textures[choose_texture(f_pts[2], 0)].size[0] * round(((int)f_pts[0] % rules->map.block)) / rules->map.block;
	}
	else
	{
		dist = final_length(xy[0], xy[1], s_pts);
		chosen = &rules->textures[choose_texture(s_pts[2], 1)];
		color_unit_x = chosen->size[0] * round(((int)s_pts[1] % rules->map.block)) / rules->map.block;
	}
	dist *= cos(angle_diff);
	draw_texture(counter, dist, rules, scene, color_unit_x, chosen);
}
