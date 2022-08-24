/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:06:51 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 14:59:03 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_coordinates(t_rules *rules, char *dir, int next_c[2])
{
	if (!ft_strncmp(dir, "up", 2))
	{
		next_c[0] = rules->player.x;
		next_c[1] = rules->player.y - rules->map.block / 10;
	}
	else if (!ft_strncmp(dir, "down", 4))
	{
		next_c[0] = rules->player.x;
		next_c[1] = rules->player.y + rules->map.block / 10;
	}
	else if (!ft_strncmp(dir, "left", 4))
	{
		next_c[0] = rules->player.x - rules->map.block / 10;
		next_c[1] = rules->player.y;
	}
	else if (!ft_strncmp(dir, "right", 5))
	{
		next_c[0] = rules->player.x + rules->map.block / 10;
		next_c[1] = rules->player.y;
	}
}

int	verify_collide(t_rules *rules, char *dir, int next_c[2])
{
	if (!ft_strncmp(dir, "left", 4))
	{
		if (rules->map.map[next_c[1] / rules->map.block]
			[next_c[0] / rules->map.block] == '1')
			return (1);
	}
	else if (!ft_strncmp(dir, "right", 5))
	{
		if (rules->map.map[next_c[1] / rules->map.block]
			[next_c[0] / rules->map.block] == '1')
			return (1);
	}
	else if (!ft_strncmp(dir, "up", 2))
	{
		if (rules->map.map[next_c[1] / rules->map.block]
			[next_c[0] / rules->map.block] == '1')
			return (1);
	}
	else if (!ft_strncmp(dir, "down", 4))
	{
		if (rules->map.map[next_c[1] / rules->map.block]
			[next_c[0] / rules->map.block] == '1')
			return (1);
	}
	return (0);
}

int	verify_collide2(t_rules *rules, int next[2])
{
	if (next[0] < 0 || next[1] < 0
		|| next[0] > rules->map.map_width
		|| next[1] > rules->map.map_height)
		return (1);
	if (rules->map.map[next[1]][next[0]] == '1')
		return (1);
	return (0);
}

int	virtual_horizontal_colliding(int ray_x, int ray_y, t_rules *rules, int dir)
{
	int	map_x;
	int	map_y;

	map_x = ray_x / rules->map.block;
	if (!dir)
		map_y = ray_y / rules->map.block - 1;
	else
		map_y = ray_y / rules->map.block;
	if (map_x < 0 || map_y < 0
		|| map_x > rules->map.map_width
		|| map_y > rules->map.map_height)
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
		map_x = ray_x / rules->map.block;
	else
		map_x = ray_x / rules->map.block - 1;
	map_y = ray_y / rules->map.block;
	if (map_x < 0 || map_y < 0
		|| map_x > rules->map.map_width - 1
		|| map_y > rules->map.map_height - 1)
		return (1);
	if (rules->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	colliding2(t_rules *rules, float ray_cos, float ray_sin, int plus)
{
	int	next_c[2];
	int	act[2];
	int	next[2];

	act[0] = rules->player.x / rules->map.block;
	act[1] = rules->player.y / rules->map.block;
	if (plus)
	{
		get_next_plus(rules, ray_cos, ray_sin, next);
		get_next_c_plus(rules, ray_cos, ray_sin, next_c);
	}
	else
	{
		get_next_minus(rules, ray_cos, ray_sin, next);
		get_next_c_minus(rules, ray_cos, ray_sin, next_c);
	}
	if (act[0] != next[0] || act[1] != next[1]
		|| !(next_c[0] % rules->map.block)
		|| !(next_c[1] % rules->map.block))
	{
		if (verify_collide2(rules, next))
			return (1);
	}
	return (0);
}

int	colliding(t_rules *rules, char *dir)
{
	int	next_c[2];
	int	act[2];
	int	next[2];

	act[0] = rules->player.x / rules->map.block;
	act[1] = rules->player.y / rules->map.block;
	next_coordinates(rules, dir, next_c);
	next[0] = next_c[0] / rules->map.block;
	next[1] = next_c[1] / rules->map.block;
	if (act[0] != next[0] || act[1] != next[1]
		|| !(next_c[0] % rules->map.block)
		|| !(next_c[1] % rules->map.block))
	{
		if (verify_collide(rules, dir, next))
			return (1);
	}
	return (0);
}
