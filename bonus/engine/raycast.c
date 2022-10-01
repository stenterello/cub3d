/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:56:50 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 15:04:55 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	if (rules->map.map[map_y][map_x] == '1'
		|| rules->map.map[map_y][map_x] == '2')
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
	if (rules->map.map[map_y][map_x] == '1'
		|| rules->map.map[map_y][map_x] == '2')
		return (1);
	return (0);
}

void	raycast(t_rules *rules, t_image *view, t_image *minimap)
{
	t_bres_data	data;

	data.ray_angle = increment_angle(rules->player.dir,
			rules->mlx.win_width / 4);
	data.x = 0;
	data.color = 0x00FFFFFF;
	while (data.x++ < rules->mlx.win_width - 1)
		calc_ray(&data, rules, view, minimap);
}
