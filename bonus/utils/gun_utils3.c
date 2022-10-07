/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:43:50 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/07 12:01:12 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	vertical_lines_check_enemy(double angle, t_rules *rules, float ret[3])
{
	t_ray	ray;
	double	n_tan;
	float	xy[2];

	xy[0] = rules->player.x;
	xy[1] = rules->player.y;
	ray.angle = angle;
	n_tan = -tan(ray.angle);
	ret[2] = define_ver_ray_and_offset(rules, &ray, n_tan, xy);
	while (!virtual_vertical_colliding_enemy(ray, rules, ret[2]))
	{
		ray.x += ray.xyoff[0];
		ray.y += ray.xyoff[1];
	}
	if (virtual_vertical_colliding_enemy(ray, rules, ret[2]) == 2)
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

void	kill_enemy_supp(t_rules *rules, int i, int map_x, int map_y)
{
	while (++i < rules->n_sprites)
	{
		if (rules->spr[i].mini_x == map_x && rules->spr[i].mini_y == map_y
			&& rules->spr[i].state && rules->spr[i].type)
		{
			rules->spr[i].dying = 6;
			rules->spr[i].attacking = 0;
			rules->spr[i].type = 1;
			rules->map.map[map_y][map_x] = '6';
		}
	}
}

void	kill_enemy(t_rules *rules, float pts[3])
{
	int			map_x;
	int			map_y;
	int			i;

	map_x = 0;
	map_y = 0;
	if (!((int)pts[0] % (int)rules->map.block_width))
	{
		if (!pts[2])
			map_x = pts[0] / (int)rules->map.block_width;
		else
			map_x = pts[0] / (int)rules->map.block_width - 1;
		map_y = pts[1] / (int)rules->map.block_width;
	}
	else if (!((int)pts[1] % (int)rules->map.block_width))
	{
		map_x = pts[0] / rules->map.block_width;
		if (!pts[2])
			map_y = pts[1] / rules->map.block_width - 1;
		else
			map_y = pts[1] / rules->map.block_width;
	}
	i = -1;
	kill_enemy_supp(rules, i, map_x, map_y);
}
