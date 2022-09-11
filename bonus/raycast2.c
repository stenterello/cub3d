/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:55:01 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/12 00:54:11 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	define_hor_ray_and_offset(t_rules *rules, t_ray *ray,
	double a_tan, float xy[2])
{
	if (ray->angle < M_PI)
	{
		ray->y = xy[1] - (rules->map.block_width - (rules->map.block_width
					- our_modulo(xy[1], rules->map.block_width)));
		ray->x = (xy[1] - ray->y) * a_tan + xy[0];
		ray->xyoff[1] = -rules->map.block_width;
		ray->xyoff[0] = -ray->xyoff[1] * a_tan;
		return (0);
	}
	else
	{
		ray->y = xy[1] + (rules->map.block_width - our_modulo(xy[1],
					rules->map.block_width));
		ray->x = (xy[1] - ray->y) * a_tan + xy[0];
		ray->xyoff[1] = rules->map.block_width;
		ray->xyoff[0] = -ray->xyoff[1] * a_tan;
		return (1);
	}
}

void	horizontal_lines_check(double angle, t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	a_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	ray.angle = angle;
	a_tan = 1 / tan(ray.angle);
	ret[2] = define_hor_ray_and_offset(rules, &ray, a_tan, xy);
	while (!virtual_horizontal_colliding(ray.x, ray.y, rules, ret[2])
		&& ray.angle != 0 && ray.angle != (double)M_PI && ray.x != INT_MAX)
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
	if (ray->angle < M_PI / 2 || ray->angle > 3 * M_PI / 2)
	{
		ray->x = xy[0] + (rules->map.block_width - our_modulo(xy[0],
					rules->map.block_width));
		ray->y = xy[1] - (xy[0] - ray->x) * n_tan;
		ray->xyoff[0] = rules->map.block_width;
		ray->xyoff[1] = ray->xyoff[0] * n_tan;
		return (0);
	}
	else if (ray->angle >= M_PI / 2 && ray->angle <= 3 * M_PI / 2)
	{
		ray->x = xy[0] - our_modulo(xy[0], rules->map.block_width);
		ray->y = xy[1] - (xy[0] - ray->x) * n_tan;
		ray->xyoff[0] = -rules->map.block_width;
		ray->xyoff[1] = ray->xyoff[0] * n_tan;
		return (1);
	}
	return (0);
}

void	vertical_lines_check(double angle,	t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	n_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	ray.xyoff[0] = 0;
	ray.xyoff[1] = 1;
	ray.x = 0;
	ray.y = 0;
	ray.angle = angle;
	n_tan = -tan(ray.angle);
	ret[2] = define_ver_ray_and_offset(rules, &ray, n_tan, xy);
	while (!virtual_vertical_colliding(ray.x, ray.y, rules, ret[2])
		&& ray.angle != (double) M_PI / 2
		&& ray.angle != (double)(3 * M_PI / 2) && ray.x != INT_MAX)
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
	}
	ret[0] = ray.x;
	ret[1] = ray.y;
}

double	increment_angle(double angle, int t)
{
	int	i;

	i = 0;
	while (i++ < t)
	{
		angle += ANGLE_UNIT;
		if (angle > 2 * M_PI)
			angle = 0;
	}
	return (angle);
}
