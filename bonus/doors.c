/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:34:35 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/07 18:55:32 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_door(int x, int y, t_rules *rules)
{
	if (rules->map.map[y][x] == '2')
		return (1);
	return (0);
}

static int	in_front_of_door(t_rules *rules)
{
	int	x;
	int	y;

	x = (int)(rules->player.x / rules->map.block_width);
	y = (int)(rules->player.y / rules->map.block_width);
	if (rules->player.dir < M_PI / 4 || rules->player.dir > 2 * M_PI - M_PI / 4)
		x++;
	if (rules->player.dir > M_PI + M_PI / 4 && rules->player.dir < 2 * M_PI - M_PI / 4)
		y++;
	if (rules->player.dir > M_PI / 4 && rules->player.dir < M_PI - M_PI / 4)
		y--;
	if (rules->player.dir > M_PI - M_PI / 4 && rules->player.dir < M_PI + M_PI / 4)
		x--;
	if (is_door(x, y, rules))
		return (1);
	return (0);
}

static void	open_door(t_rules *rules)
{
	int	x;
	int	y;

	x = (int)(rules->player.x / rules->map.block_width);
	y = (int)(rules->player.y / rules->map.block_width);
	if (rules->player.dir < M_PI / 4 || rules->player.dir > 2 * M_PI - M_PI / 4)
		x++;
	if (rules->player.dir > M_PI + M_PI / 4 && rules->player.dir < 2 * M_PI - M_PI / 4)
		y++;
	if (rules->player.dir > M_PI / 4 && rules->player.dir < M_PI - M_PI / 4)
		y--;
	if (rules->player.dir > M_PI - M_PI / 4 && rules->player.dir < M_PI + M_PI / 4)
		x--;
	rules->map.map[y][x] = '0';
}

void	try_open_door(t_rules *rules)
{
	if (in_front_of_door(rules))
		open_door(rules);
}