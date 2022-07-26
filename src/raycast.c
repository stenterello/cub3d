/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:22:22 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 14:34:29 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	define_hor_ray_and_offset(t_rules *rules, t_ray *ray,
	double a_tan, float xy[2])
{
	if (ray->angle < PI)
	{
		ray->y = xy[1] - (rules->map.block - (rules->map.block
					- ((int)xy[1] % rules->map.block)));
		ray->x = (xy[1] - ray->y) * a_tan + xy[0];
		ray->xyoff[1] = -rules->map.block;
		ray->xyoff[0] = -ray->xyoff[1] * a_tan;
		return (0);
	}
	else
	{
		ray->y = xy[1] + (rules->map.block - ((int)xy[1] % rules->map.block));
		ray->x = (xy[1] - ray->y) * a_tan + xy[0];
		ray->xyoff[1] = rules->map.block;
		ray->xyoff[0] = -ray->xyoff[1] * a_tan;
		return (1);
	}
}

static void	horizontal_lines_check(double angle, t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	a_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	ray.angle = angle;
	a_tan = 1 / tan(ray.angle);
	if (ray.angle == 0 || ray.angle == (double)PI)
	{
		ray.x = INT_MAX; // not so secure...
		ray.y = INT_MAX;
		ret[2] = 0;
	}
	else
		ret[2] = define_hor_ray_and_offset(rules, &ray, a_tan, xy);
	while (!virtual_horizontal_colliding(ray.x, ray.y, rules, ret[2])
		&& ray.angle != 0 && ray.angle != (double)PI && ray.x != INT_MAX)
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
}

static int	define_ver_ray_and_offset(t_rules *rules, t_ray *ray,
	double n_tan, float xy[2])
{
	if (ray->angle < PI / 2 || ray->angle > 3 * PI / 2)
	{
		ray->x = xy[0] + (rules->map.block - ((int)xy[0] % rules->map.block));
		ray->y = xy[1] - (xy[0] - ray->x) * n_tan;
		ray->xyoff[0] = rules->map.block;
		ray->xyoff[1] = ray->xyoff[0] * n_tan;
		return (0);
	}
	else if (ray->angle > PI / 2 || ray->angle < 3 * PI / 2)
	{
		ray->x = xy[0] - ((int)xy[0] % rules->map.block);
		ray->y = xy[1] - (xy[0] - ray->x) * n_tan;
		ray->xyoff[0] = -rules->map.block;
		ray->xyoff[1] = ray->xyoff[0] * n_tan;
		return (1);
	}
	return (0);
}

static void	vertical_lines_check(double angle,
	t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	n_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	ray.angle = angle;
	n_tan = -tan(ray.angle);
	if (ray.angle == (double)PI / 2 || ray.angle == (double)(3 * PI / 2))
	{
		ray.x = INT_MAX;
		ray.y = INT_MAX;
		ret[2] = 0;
	}
	else
		ret[2] = define_ver_ray_and_offset(rules, &ray, n_tan, xy);
	while (!virtual_vertical_colliding(ray.x, ray.y, rules, ret[2])
		&& ray.angle != (double)PI / 2
		&& ray.angle != (double)(3 * PI / 2) && ray.x != INT_MAX)
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
}

void	raycast_bresenham(double angle, t_rules *rules, t_frame *scene)
{
	float		f_pts[3];
	float		s_pts[3];

	horizontal_lines_check(angle, rules, f_pts);
	vertical_lines_check(angle, rules, s_pts);
	if (final_length(rules->player.x, rules->player.y, s_pts) == INT_MAX
		|| final_length(rules->player.x, rules->player.y, f_pts)
		< final_length(rules->player.x, rules->player.y, s_pts))
		define_paint(rules, f_pts, angle, scene);
	else
		define_paint(rules, s_pts, angle, scene);
}
