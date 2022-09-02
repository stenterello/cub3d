/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:44:07 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/02 17:28:07 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall(t_rules rules, float x, float y)
{
	if ((int)(x / rules.map.block_width) < 0
		|| (int)(y / rules.map.block_width) < 0
		|| (int)(x / rules.map.block_width) > rules.map.map_height_len[0] - 1
		|| (int)(y / rules.map.block_width) > rules.map.map_height_len[1] - 1)
		return (1);
	if (rules.map.map[(int)(y / rules.map.block_width)]
		[(int)(x / rules.map.block_width)] == '1')
		return (1);
	return (0);
}

int	verify_collide(t_rules *rules, int next[2])
{
	if (next[0] < 0 || next[1] < 0
		|| next[0] > rules->map.map_height_len[0]
		|| next[1] > rules->map.map_height_len[1])
		return (1);
	if (rules->map.map[next[1]][next[0]] == '1')
		return (1);
	return (0);
}

int	colliding(t_rules *rules, float ray_cos, float ray_sin, int plus)
{
	int	next_c[2];
	int	act[2];
	int	next[2];

	act[0] = rules->player.x / rules->map.block_width;
	act[1] = rules->player.y / rules->map.block_width;
	if (plus)
	{
		get_next_plus(rules, ray_cos, ray_sin, next);
		get_next_c_plus(rules, ray_cos, ray_sin, next_c);
	}
	else
	{
		get_next_minus(rules, ray_cos, ray_sin, next);
		get_c_minus(rules, ray_cos, ray_sin, next_c);
	}
	if (act[0] != next[0] || act[1] != next[1]
		|| !(next_c[0] % (int)rules->map.block_width)
		|| !(next_c[1] % (int)rules->map.block_width))
	{
		if (verify_collide(rules, next))
			return (1);
	}
	return (0);
}
