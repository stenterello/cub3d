/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_colliding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:46:51 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 20:10:51 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mini_virtual_horizontal_colliding(float ray_x, float ray_y,
	t_rules *rules, int dir)
{
	int	map_x;
	int	map_y;

	map_x = (ray_x - 2) / rules->map.mini_block;
	if (!dir)
		map_y = ray_y / rules->map.mini_block - 1;
	else
		map_y = ray_y / rules->map.mini_block;
	if (map_x < 0 || map_y < 0
		|| map_x > rules->map.map_width || map_y > rules->map.map_height)
		return (1);
	if (rules->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	mini_virtual_vertical_colliding(int ray_x, int ray_y,
	t_rules *rules, int dir)
{
	int	map_x;
	int	map_y;

	if (!dir)
		map_x = ray_x / rules->map.mini_block;
	else
		map_x = ray_x / rules->map.mini_block - 1;
	map_y = ray_y / rules->map.mini_block;
	if (map_x < 0 || map_y < 0
		|| map_x > rules->map.map_width - 1
		|| map_y > rules->map.map_height - 1)
		return (1);
	if (rules->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	get_next_plus(t_rules *rules, float ray_cos, float ray_sin, int next[2])
{
	next[0] = (rules->player.x + ray_cos) / rules->map.block;
	next[1] = (rules->player.y + ray_sin) / rules->map.block;
}

void	get_next_minus(t_rules *rules, float ray_cos, float ray_sin, int next[2])
{
	next[0] = (rules->player.x - ray_cos) / rules->map.block;
	next[1] = (rules->player.y - ray_sin) / rules->map.block;
}

void	get_next_c_plus(t_rules *rules, float ray_cos, float ray_sin, int next_c[2])
{
	next_c[0] = rules->player.x + ray_cos;
	next_c[1] = rules->player.y + ray_sin;
}

void	get_next_c_minus(t_rules *rules, float ray_cos, float ray_sin, int next_c[2])
{
	next_c[0] = rules->player.x - ray_cos;
	next_c[1] = rules->player.y - ray_sin;
}
