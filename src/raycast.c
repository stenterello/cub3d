/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:28:56 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/01 21:46:58 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	final_length(float start_x, float start_y, float rxy[2])
{
	if (rxy[0] == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(get_abs(start_x - rxy[0]), 2) + pow(start_y - rxy[1], 2)));
}

int	virtual_horizontal_colliding(int ray_x, int ray_y, t_rules *rules, int dir)
{
	int	map_x;
	int	map_y;

	map_x = ray_x / rules->map.block_width;
	if (!dir)
		map_y = ray_y / rules->map.block_width - 1;
	else
		map_y = ray_y / rules->map.block_width;
	if (map_x < 0 || map_y < 0
		|| map_x > rules->map.map_height_len[0] - 1
		|| map_y > rules->map.map_height_len[1] - 1)
		return (1);
	if (rules->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	virtual_vertical_colliding(int ray_x, int ray_y, t_rules *rules, int dir)
{
	int	map_x;
	int	map_y;

	if (!dir)
		map_x = ray_x / (int)rules->map.block_width;
	else
		map_x = ray_x / (int)rules->map.block_width - 1;
	map_y = ray_y / (int)rules->map.block_width;
	if (map_x < 0 || map_y < 0
		|| map_x > rules->map.map_height_len[0] - 1
		|| map_y > rules->map.map_height_len[1] - 1)
		return (1);
	if (rules->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

static int	define_hor_ray_and_offset(t_rules *rules, t_ray *ray,
	double a_tan, float xy[2])
{
	if (ray->angle < M_PI)
	{
		ray->y = xy[1] - (rules->map.block_width - (rules->map.block_width
					- ((int)xy[1] % (int)rules->map.block_width)));
		ray->x = (xy[1] - ray->y) * a_tan + xy[0];
		ray->xyoff[1] = -rules->map.block_width;
		ray->xyoff[0] = -ray->xyoff[1] * a_tan;
		return (0);
	}
	else
	{
		ray->y = xy[1] + (rules->map.block_width - ((int)xy[1] % (int)rules->map.block_width));
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
		ray->x = xy[0] + (rules->map.block_width - ((int)xy[0] % (int)rules->map.block_width));
		ray->y = xy[1] - (xy[0] - ray->x) * n_tan;
		ray->xyoff[0] = rules->map.block_width;
		ray->xyoff[1] = ray->xyoff[0] * n_tan;
		return (0);
	}
	else if (ray->angle >= M_PI / 2 && ray->angle <= 3 * M_PI / 2)
	{
		ray->x = xy[0] - ((int)xy[0] % (int)rules->map.block_width);
		ray->y = xy[1] - (xy[0] - ray->x) * n_tan;
		ray->xyoff[0] = -rules->map.block_width;
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

double	decrement_angle(double angle, int t)
{
	int	i;

	i = 0;
	while (i++ < t)
	{
		angle -= ANGLE_UNIT;
		if (angle < 0)
			angle = 2 * M_PI;
	}
	return (angle);
}

int	times(double dir1, double dir2)
{
	int	ret;

	ret = 0;
	if (dir1 > dir2)
	{
		while (dir1 > dir2)
		{
			dir1 = decrement_angle(dir1, 1);
			ret++;
		}
	}
	else
	{
		while (dir1 < dir2)
		{
			dir1 = increment_angle(dir1, 1);
			ret++;
		}
	}
	return (ret);
}

void	raycast(t_rules *rules, t_image *image)
{
	float	f_pts[3];
	float	s_pts[3];
	float	src[2];
	double	dir1;
	int		i;

	dir1 = increment_angle(rules->player.dir, 45);
	i = 0;
	while (i++ < 200)
	{
		horizontal_lines_check(dir1, rules, f_pts);
		vertical_lines_check(dir1, rules, s_pts);
		src[0] = rules->player.x;
		src[1] = rules->player.y;
		if (final_length(rules->player.x, rules->player.y, s_pts) == INT_MAX
			|| final_length(rules->player.x, rules->player.y, f_pts)
			< final_length(rules->player.x, rules->player.y, s_pts))
		{
			bresenham(src, f_pts, 0x00FFFFFF, image);
		}
		else
		{
			bresenham(src, s_pts, 0x00FFFFFF, image);
		}
		dir1 = decrement_angle(dir1, 1);
	}
}
