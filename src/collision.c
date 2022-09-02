/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:44:07 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 12:44:45 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall(t_rules rules, float x, float y)
{
	if ((int)(x / rules.map.block_width) < 0 || (int)(y / rules.map.block_width) < 0
		|| (int)(x / rules.map.block_width) > rules.map.map_height_len[0] - 1
		|| (int)(y / rules.map.block_width) > rules.map.map_height_len[1] - 1)
		return (1);
	if (rules.map.map[(int)(y / rules.map.block_width)][(int)(x / rules.map.block_width)] == '1')
		return (1);
	return (0);
}

int	wall_coll(t_rules rules, float x, float y)
{
	if (x == 1)
		rules.player.x += (rules.map.block_width / 10) + 1;
	else if (x == -1)
		rules.player.x -= ((rules.map.block_width / 10) + 1);
	else if (y == 1)
		rules.player.y += (rules.map.block_width / 10) + 1;
	else if (y == -1)
		rules.player.y -= ((rules.map.block_width / 10) + 1);
	if (wall(rules, rules.player.x, rules.player.y))
		return (1);
	return (0);
}