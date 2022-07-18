/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 21:06:51 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/18 12:32:13 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void next_coordinates(t_rules *rules, char *dir, int next_c[2])
{
	if (!ft_strncmp(dir, "up", 2))
	{
		next_c[0] = rules->player.x;
		next_c[1] = rules->player.y - 1;
	}
	else if (!ft_strncmp(dir, "down", 4))
	{
		next_c[0] = rules->player.x;
		next_c[1] = rules->player.y + 1;
	}
	else if (!ft_strncmp(dir, "left", 4))
	{
		next_c[0] = rules->player.x - 1;
		next_c[1] = rules->player.y;
	}
	else if (!ft_strncmp(dir, "right", 5))
	{
		next_c[0] = rules->player.x + 1;
		next_c[1] = rules->player.y;
	}
}

int verify_collide(t_rules *rules, char *dir, int next_c[2])
{
	if (!(next_c[0] % rules->mini_block_width) && !ft_strncmp(dir, "left", 4))
	{
		if (rules->map[next_c[1] / rules->mini_block_width][next_c[0] / rules->mini_block_width - 1] == '1')
			return (1);
	}
	else if (!(next_c[0] % rules->mini_block_width) && !ft_strncmp(dir, "right", 5))
	{
		if (rules->map[next_c[1] / rules->mini_block_width - 1][next_c[0] / rules->mini_block_width] == '1')
			return (1);
	}
	else if (!(next_c[1] % rules->mini_block_width) && !ft_strncmp(dir, "up", 2))
	{
		if (rules->map[next_c[1] / rules->mini_block_width - 1][next_c[0] / rules->mini_block_width] == '1')
			return (1);
	}
	else if (!(next_c[1] % rules->mini_block_width) && !ft_strncmp(dir, "down", 4))
	{
		if (rules->map[next_c[1] / rules->mini_block_width][next_c[0] / rules->mini_block_width] == '1')
			return (1);
	}
	return (0);
}

int	virtual_horizontal_colliding(int rayX, int rayY, t_rules *rules, int dir)
{
	int	mapX;
	int	mapY;

	mapX = rayX / rules->mini_block_width;
	if (!dir)
		mapY = rayY / rules->mini_block_width - 1;
	else
		mapY = rayY / rules->mini_block_width;
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
		mapX = rayX / rules->mini_block_width;
	else
		mapX = rayX / rules->mini_block_width - 1;
	mapY = rayY / rules->mini_block_width;
	if (mapX < 0 || mapY < 0 || mapX > rules->map_width - 1 || mapY > rules->map_height - 1)
		return (1);
	if (rules->map[mapY][mapX] == '1')
		return (1);
	return (0);
}

int colliding(t_rules *rules, char *dir)
{
	int next_c[2];

	next_coordinates(rules, dir, next_c);
	if (!(next_c[0] % rules->mini_block_width) || !(next_c[1] % rules->mini_block_width))
	{
		if (verify_collide(rules, dir, next_c))
			return (1);
	}
	return (0);
}
