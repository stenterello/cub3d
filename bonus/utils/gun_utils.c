/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:10:18 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 11:44:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_gun(t_rules *rules)
{
	t_image	*gun;

	gun = &rules->player.gun.gun_img;
	gun->img = mlx_xpm_file_to_image(rules->mlx.mlx, rules->player.gun.path,
			&gun->width, &gun->height);
	if (!gun->img)
		die("Could not load textures. Aborting");
	gun->addr = mlx_get_data_addr(gun->img, &gun->bpp, &gun->line_length,
			&gun->endian);
}

int	goes_to_center(t_ray ray, t_rules *rules)
{
	float	inside_coord[2];
	float	en_coord[2];
	float	k[2];

	inside_coord[0] = our_modulo(ray.x, rules->map.block_width);
	inside_coord[1] = our_modulo(ray.y, rules->map.block_width);
	en_coord[0] = rules->map.block_width / 2;
	en_coord[1] = rules->map.block_width / 2;
	if (ray.xyoff[0] < 0)
		k[0] = -ray.xyoff[0] / 10;
	else
		k[0] = ray.xyoff[0] / 10;
	if (ray.xyoff[1] < 0)
		k[1] = -ray.xyoff[1] / 10;
	else
		k[1] = ray.xyoff[1] / 10;
	while (inside_coord[0] < rules->map.block_width && inside_coord[0] >= 0
		&& inside_coord[1] >= 0 && inside_coord[1] < rules->map.block_width)
	{
		if (final_length(inside_coord[0], inside_coord[1], en_coord) < 3.5)
			return (1);
		inside_coord[0] += k[0];
		inside_coord[1] += k[1];
	}
	return (0);
}

int	virtual_vertical_colliding_enemy(t_ray ray, t_rules *rules, int dir)
{
	int		map_x;
	int		map_y;

	if (!dir)
		map_x = ray.x / (int)rules->map.block_width;
	else
		map_x = ray.x / (int)rules->map.block_width - 1;
	map_y = ray.y / (int)rules->map.block_width;
	if (map_x < 0 || map_y < 0
		|| map_x > rules->map.map_height_len[0] - 1
		|| map_y > rules->map.map_height_len[1] - 1)
		return (2);
	if (rules->map.map[map_y][map_x] == '4' && goes_to_center(ray, rules))
		return (1);
	return (0);
}

int	virtual_horizontal_colliding_enemy(t_ray ray, t_rules *rules, int dir)
{
	int		map_x;
	int		map_y;

	map_x = ray.x / rules->map.block_width;
	if (!dir)
		map_y = ray.y / rules->map.block_width - 1;
	else
		map_y = ray.y / rules->map.block_width;
	if (map_x < 0 || map_y < 0
		|| map_x > rules->map.map_height_len[0] - 1
		|| map_y > rules->map.map_height_len[1] - 1)
		return (2);
	if (rules->map.map[map_y][map_x] == '4' && goes_to_center(ray, rules))
		return (1);
	return (0);
}

void	horizontal_lines_check_enemy(double angle, t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	a_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	ray.angle = angle;
	a_tan = 1 / tan(ray.angle);
	ret[2] = define_hor_ray_and_offset(rules, &ray, a_tan, xy);
	while (!virtual_horizontal_colliding_enemy(ray, rules, ret[2]))
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
	}
	if (virtual_horizontal_colliding_enemy(ray, rules, ret[2]) == 2)
	{
		ret[0] = 0;
		ret[1] = 0;
	}
	else
	{
		ret[0] = ray.x;
		ret[1] = ray.y;
	}
}
