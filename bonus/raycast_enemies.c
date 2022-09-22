/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:53:34 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/22 19:15:03 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	virtual_vertical_colliding_enemies(int ray_x, int ray_y, t_rules *rules, int dir)
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
	if (rules->map.map[map_y][map_x] == '4')
		return (1);
	return (0);
}

int	virtual_horizontal_colliding_enemies(int ray_x, int ray_y, t_rules *rules, int dir)
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
	if (rules->map.map[map_y][map_x] == '4')
		return (1);
	return (0);
}

void	horizontal_lines_check_enemies(double angle, t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	a_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	ray.angle = angle;
	a_tan = 1 / tan(ray.angle);
	ret[2] = define_hor_ray_and_offset(rules, &ray, a_tan, xy);
	while (ray.x != INT_MAX && ray.x > 0 && ray.x / rules->map.block_width < rules->map.map_height_len[0]
		&& ray.y > 0 && ray.y / rules->map.block_width < rules->map.map_height_len[1]
		&& !virtual_horizontal_colliding_enemies(ray.x, ray.y, rules, ret[2])
		&& ray.angle != 0 && ray.angle != (double)M_PI)
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
	}
	if (ray.x != INT_MAX && ray.x > 0 && ray.x / rules->map.block_width < rules->map.map_height_len[0]
		&& ray.y > 0 && ray.y / rules->map.block_width < rules->map.map_height_len[1])
	{
		ret[0] = ray.x;
		ret[1] = ray.y;
	}
	else
	{
		ret[0] = 0;
		ret[1] = 0;
	}
}

void	vertical_lines_check_enemies(double angle, t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	n_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	ray.angle = angle;
	n_tan = -tan(ray.angle);
	ret[2] = define_ver_ray_and_offset(rules, &ray, n_tan, xy);
	while (ray.x != INT_MAX && ray.x > 0 && ray.x / rules->map.block_width < rules->map.map_height_len[0]
		&& ray.y > 0 && ray.y / rules->map.block_width < rules->map.map_height_len[1]
		&& !virtual_vertical_colliding_enemies(ray.x, ray.y, rules, ret[2])
		&& ray.angle != (double) M_PI / 2
		&& ray.angle != (double)(3 * M_PI / 2) && ray.x != INT_MAX)
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
	}
	if (ray.x != INT_MAX && ray.x > 0 && ray.x / rules->map.block_width < rules->map.map_height_len[0]
		&& ray.y > 0 && ray.y / rules->map.block_width < rules->map.map_height_len[1])
	{
		ret[0] = ray.x;
		ret[1] = ray.y;
	}
	else
	{
		ret[0] = 0;
		ret[1] = 0;
	}
}

void	there_is_enemy(t_bres_data *data, t_rules *rules, float coord[2])
{
	float		f_pts[3];
	float		s_pts[3];

	horizontal_lines_check_enemies(data->dir1, rules, f_pts);
	vertical_lines_check_enemies(data->dir1, rules, s_pts);
	if (f_pts[0] != 0 && f_pts[1] != 0)
	{
		if (our_modulo(f_pts[0], rules->map.block_width))
			f_pts[0] = f_pts[0] - our_modulo(f_pts[0], rules->map.block_width);
		else if (our_modulo(f_pts[1], rules->map.block_width))
			f_pts[1] = f_pts[1] - our_modulo(f_pts[1], rules->map.block_width);
		coord[0] = f_pts[0] + rules->map.block_width / 2;
		coord[1] = f_pts[1] + rules->map.block_width / 2;
	}
	else if (s_pts[0] != 0 && s_pts[1] != 0)
	{
		if (our_modulo(s_pts[0], rules->map.block_width))
			s_pts[0] = s_pts[0] - our_modulo(s_pts[0], rules->map.block_width);
		else if (our_modulo(s_pts[1], rules->map.block_width))
			s_pts[1] = s_pts[1] - our_modulo(s_pts[1], rules->map.block_width);
		coord[0] = s_pts[0] + rules->map.block_width / 2;
		coord[1] = s_pts[1] + rules->map.block_width / 2;
	}
}

int	enemy_in_view(double dir, t_rules *rules, float coord[2])
{
	float	f_pts[3];
	float	s_pts[3];

	horizontal_lines_check_enemies(dir, rules, f_pts);
	vertical_lines_check_enemies(dir, rules, s_pts);
	if (f_pts[0] || f_pts[1])
	{
		coord[1] = f_pts[1] - rules->map.block_width / 2;
		coord[0] = f_pts[0] - our_modulo(f_pts[0], rules->map.block_width) + rules->map.block_width * 2;
		return (1);
	}
	if (s_pts[0] || s_pts[1])
	{
		coord[0] = s_pts[0] + rules->map.block_width / 2;
		coord[1] = s_pts[1] - our_modulo(s_pts[1], rules->map.block_width) + rules->map.block_width / 2;
		return (1);
	}
	return (0);
}

void	draw_enemy(t_rules *rules, t_bres_data *data, t_image *view)
{
	double	dist;
	int		y;
	int		y2;
	double	l_h;
	int		x2;

	dist = get_dist(rules, *data);
	l_h = rules->map.block_width * rules->mlx.win_height / dist;
	x2 = data->x + 4;
	while (data->x < x2)
	{
		y = rules->mlx.win_height / 2 - l_h / 2;
		y2 = rules->mlx.win_height / 2 + l_h / 2;
		while (y < y2)
		{
			easy_pxl(view, data->x, y,
				0x00000000);
			y++;
		}
		data->x++;
	}
}

void	check_enemy(t_bres_data *data, t_rules *rules, t_image *view)
{
	if (enemy_in_view(data->dir1, rules, data->xy2))
		draw_enemy(rules, data, view);
	else
		data->x += 4;
	data->dir1 = decrement_angle(data->dir1, 2);
}

void	raycast_enemies(t_rules *rules, t_image *view)
{
	int			i;
	t_bres_data	data;

	data.dir1 = increment_angle(rules->player.dir,
			rules->mlx.win_width / 3.79259259);
	i = 0;
	data.x = 0;
	while (i++ < rules->mlx.win_width / 3.66)
		check_enemy(&data, rules, view);
}