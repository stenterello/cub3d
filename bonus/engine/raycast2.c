/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:55:01 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 15:03:24 by ddelladi         ###   ########.fr       */
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

static void	horizontal_lines_check(double angle, t_rules *rules, float ret[3])
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

static void	vertical_lines_check(double angle,	t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	n_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
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

void	calc_ray(t_bres_data *data, t_rules *rules,
	t_image *view, t_image *minimap)
{
	float		f_pts[3];
	float		s_pts[3];

	horizontal_lines_check(data->ray_angle, rules, f_pts);
	vertical_lines_check(data->ray_angle, rules, s_pts);
	data->xy[0] = rules->player.x;
	data->xy[1] = rules->player.y;
	if (final_length(rules->player.x, rules->player.y, s_pts) == INT_MAX
		|| final_length(rules->player.x, rules->player.y, f_pts)
		< final_length(rules->player.x, rules->player.y, s_pts))
	{
		data->xy2[0] = f_pts[0];
		data->xy2[1] = f_pts[1];
		bresenham(data, minimap, view, rules);
	}
	else
	{
		data->xy2[0] = s_pts[0];
		data->xy2[1] = s_pts[1];
		bresenham(data, minimap, view, rules);
	}
	data->ray_angle = decrement_angle(data->ray_angle, 1);
}
