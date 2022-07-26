/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:31:29 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 14:47:14 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	define_mini_hor_ray_and_offset(t_rules *rules, t_ray *ray,
	double a_tan, float xy[2])
{
	if (ray->angle < PI)
	{
		ray->y = xy[1] - (rules->map.mini_block - (rules->map.mini_block
					- ((int)xy[1] % rules->map.mini_block)));
		ray->x = (xy[1] - ray->y) * a_tan + xy[0];
		ray->xyoff[1] = -rules->map.mini_block;
		ray->xyoff[0] = -ray->xyoff[1] * a_tan;
		return (0);
	}
	else if (ray->angle > PI)
	{
		ray->y = xy[1] + (rules->map.mini_block - ((int)xy[1]
					% rules->map.mini_block));
		ray->x = (xy[1] - ray->y) * a_tan + xy[0];
		ray->xyoff[1] = rules->map.mini_block;
		ray->xyoff[0] = -ray->xyoff[1] * a_tan;
		return (1);
	}
	return (0);
}

void	mini_horizontal_lines_check(double angle, float xy[2],
	t_rules *rules, float ret[2])
{
	t_ray	ray;
	double	a_tan;

	ray.angle = angle;
	a_tan = 1 / tan(ray.angle);
	if (ray.angle == 0 || ray.angle == (double)PI)
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
		ret[2] = 0;
	}
	else
		ret[2] = define_mini_hor_ray_and_offset(rules, &ray, a_tan, xy);
	while (!mini_virtual_horizontal_colliding(ray.x, ray.y, rules, ret[2])
		&& ray.angle != 0 && ray.angle != (double)PI
		&& ray.x != INT_MAX)
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
}

static int	define_mini_ver_ray_and_offset(t_rules *rules, t_ray *ray,
	double n_tan, float xy[2])
{
	if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		ray->x = xy[0] + (rules->map.mini_block - ((int)xy[0]
					% rules->map.mini_block));
		ray->y = xy[1] - (xy[0] - ray->x) * n_tan;
		ray->xyoff[0] = rules->map.mini_block;
		ray->xyoff[1] = ray->xyoff[0] * n_tan;
		return (0);
	}
	else if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
	{
		ray->x = xy[0] - ((int)xy[0] % rules->map.mini_block);
		ray->y = xy[1] - (xy[0] - ray->x) * n_tan;
		ray->xyoff[0] = -rules->map.mini_block;
		ray->xyoff[1] = ray->xyoff[0] * n_tan;
		return (1);
	}
	return (0);
}

void	mini_vertical_lines_check(double angle, float xy[2],
	t_rules *rules, float ret[2])
{
	t_ray	ray;
	double	n_tan;

	ray.angle = angle;
	n_tan = -tan(ray.angle);
	if (ray.angle == (double)PI / 2 || ray.angle == (double)(3 * PI / 2))
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
		ret[2] = 0;
	}
	else
		ret[2] = define_mini_ver_ray_and_offset(rules, &ray, n_tan, xy);
	while (!mini_virtual_vertical_colliding(ray.x, ray.y, rules, ret[2])
		&& ray.angle != (double)PI / 2
		&& ray.angle != (double)(3 * PI / 2) && ray.x != INT_MAX)
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
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
	if (final_length(xy[0], xy[1], s_pts) == INT_MAX
		|| final_length(xy[0], xy[1], f_pts)
		< final_length(xy[0], xy[1], s_pts))
		bresenham(xy, f_pts, 0x00FFFFFF, rules);
	else
		bresenham(xy, s_pts, 0x00FFFFFF, rules);
}
