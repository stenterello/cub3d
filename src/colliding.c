/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:06:51 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 21:54:26 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void next_coordinates(t_rules *rules, char *dir, int next_c[2])
{
	if (!ft_strncmp(dir, "up", 2))
	{
		next_c[0] = rules->player.x;
		next_c[1] = rules->player.y - rules->block_width / 10;
	}
	else if (!ft_strncmp(dir, "down", 4))
	{
		next_c[0] = rules->player.x;
		next_c[1] = rules->player.y + rules->block_width / 10;
	}
	else if (!ft_strncmp(dir, "left", 4))
	{
		next_c[0] = rules->player.x - rules->block_width / 10;
		next_c[1] = rules->player.y;
	}
	else if (!ft_strncmp(dir, "right", 5))
	{
		next_c[0] = rules->player.x + rules->block_width / 10;
		next_c[1] = rules->player.y;
	}
}

int verify_collide(t_rules *rules, char *dir, int next_c[2])
{
	if (!ft_strncmp(dir, "left", 4))
	{
		if (rules->map[next_c[1] / rules->block_width][next_c[0] / rules->block_width] == '1')
			return (1);
	}
	else if (!ft_strncmp(dir, "right", 5))
	{
		if (rules->map[next_c[1] / rules->block_width][next_c[0] / rules->block_width] == '1')
			return (1);
	}
	else if (!ft_strncmp(dir, "up", 2))
	{
		if (rules->map[next_c[1] / rules->block_width - 1][next_c[0] / rules->block_width] == '1')
			return (1);
	}
	else if (!ft_strncmp(dir, "down", 4))
	{
		if (rules->map[next_c[1] / rules->block_width][next_c[0] / rules->block_width] == '1')
			return (1);
	}
	return (0);
}

int	virtual_horizontal_colliding(int rayX, int rayY, t_rules *rules, int dir)
{
	int	mapX;
	int	mapY;

	mapX = rayX / rules->block_width;
	if (!dir)
		mapY = rayY / rules->block_width - 1;
	else
		mapY = rayY / rules->block_width;
	if (mapX < 0 || mapY < 0 || mapX > rules->map_width || mapY > rules->map_height)
		return (1);
	if (rules->map[mapY][mapX] == '1')
		return (1);
	return (0);
}

int	virtual_vertical_colliding(int rayX, int rayY, t_rules *rules, int dir)
{
	int	mapX;
	int	mapY;

	if (!dir)
		mapX = rayX / rules->block_width;
	else
		mapX = rayX / rules->block_width - 1;
	mapY = rayY / rules->block_width;
	if (mapX < 0 || mapY < 0 || mapX > rules->map_width - 1 || mapY > rules->map_height - 1)
		return (1);
	if (rules->map[mapY][mapX] == '1')
		return (1);
	return (0);
}

int colliding(t_rules *rules, char *dir)
{
	int next_c[2];
	int	act[2];
	int	next[2];

	act[0] = rules->player.x / rules->block_width;
	act[1] = rules->player.y / rules->block_width;
	next_coordinates(rules, dir, next_c);
	next[0] = next_c[0] / rules->block_width;
	next[1] = next_c[1] / rules->block_width;
	if (act[0] != next[0] || act[1] != next[1] || !(next_c[0] % rules->block_width) || !(next_c[1] % rules->block_width))
	{
		if (verify_collide(rules, dir, next_c))
			return (1);
	}
	return (0);
}
