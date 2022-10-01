/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:34:35 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 12:59:35 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	in_front_of_door(t_rules *rules)
{
	int	x;
	int	y;

	x = (int)(rules->player.x / rules->map.block_width);
	y = (int)(rules->player.y / rules->map.block_width);
	if (rules->player.dir < M_PI / 4 || rules->player.dir > 2 * M_PI - M_PI / 4)
		x++;
	if (rules->player.dir > M_PI + M_PI / 4
		&& rules->player.dir < 2 * M_PI - M_PI / 4)
		y++;
	if (rules->player.dir > M_PI / 4 && rules->player.dir < M_PI - M_PI / 4)
		y--;
	if (rules->player.dir > M_PI - M_PI / 4
		&& rules->player.dir < M_PI + M_PI / 4)
		x--;
	if (is_door(x, y, rules))
		return (1);
	return (0);
}

void	change_door_state(t_rules *rules)
{
	int	x;
	int	y;

	x = (int)(rules->player.x / rules->map.block_width);
	y = (int)(rules->player.y / rules->map.block_width);
	if (rules->player.dir < M_PI / 4 || rules->player.dir > 2 * M_PI - M_PI / 4)
		x++;
	if (rules->player.dir > M_PI + M_PI / 4
		&& rules->player.dir < 2 * M_PI - M_PI / 4)
		y++;
	if (rules->player.dir > M_PI / 4 && rules->player.dir < M_PI - M_PI / 4)
		y--;
	if (rules->player.dir > M_PI - M_PI / 4
		&& rules->player.dir < M_PI + M_PI / 4)
		x--;
	if (rules->map.map[y][x] == '2')
		rules->map.map[y][x] = '3';
	else
		rules->map.map[y][x] = '2';
	rules->last_door_action = rules->n_frames;
}

void	interact_with_door(t_rules *rules)
{
	if (in_front_of_door(rules)
		&& rules->n_frames - rules->last_door_action > 350)
		change_door_state(rules);
}

int	is_door(int x, int y, t_rules *rules)
{
	if (rules->map.map[y][x] == '2' || rules->map.map[y][x] == '3')
		return (1);
	return (0);
}

