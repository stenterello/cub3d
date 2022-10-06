/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:44:07 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/06 17:24:59 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	turn_off_sprite(t_rules *rules, int next[2])
{
	int	i;

	i = -1;
	while (++i < rules->n_sprites)
	{
		if (rules->spr[i].mini_x == next[0] && rules->spr[i].mini_y == next[1])
		{
			rules->spr[i].state = 0;
			return ;
		}
	}
}

static int	verify_collide(t_rules *rules, int next[2])
{
	if (next[0] < 0 || next[1] < 0
		|| next[0] > rules->map.map_height_len[0]
		|| next[1] > rules->map.map_height_len[1])
		return (1);
	if (rules->map.map[next[1]][next[0]] == '1'
			|| rules->map.map[next[1]][next[0]] == '2')
		return (1);
	if (rules->map.map[next[1]][next[0]] == '4')
		return (2);
	if (rules->map.map[next[1]][next[0]] == '5')
	{
		rules->map.map[next[1]][next[0]] = '7';
		turn_off_sprite(rules, next);
		return (3);
	}
	return (0);
}

static void	get_next(t_rules *rules, float sin_cos[2], int next[2], int flag)
{
	if (flag)
	{
		next[0] = (rules->player.x + sin_cos[1]) / rules->map.block_width;
		next[1] = (rules->player.y + sin_cos[0]) / rules->map.block_width;
	}
	else
	{
		next[0] = (rules->player.x - sin_cos[1]) / rules->map.block_width;
		next[1] = (rules->player.y - sin_cos[0]) / rules->map.block_width;
	}
}

static void	get_next_c(t_rules *rules, float sin_cos[2], int next_c[2], int flag)
{
	if (flag)
	{
		next_c[0] = rules->player.x + sin_cos[1];
		next_c[1] = rules->player.y + sin_cos[0];
	}
	else
	{
		next_c[0] = rules->player.x - sin_cos[1];
		next_c[1] = rules->player.y - sin_cos[0];
	}
}

int	colliding(t_rules *rules, float ray_cos, float ray_sin, int plus)
{
	int		next_c[2];
	int		act[2];
	int		next[2];
	float	sin_cos[2];

	act[0] = rules->player.x / rules->map.block_width;
	act[1] = rules->player.y / rules->map.block_width;
	sin_cos[0] = ray_sin;
	sin_cos[1] = ray_cos;
	if (plus)
	{
		get_next(rules, sin_cos, next, 1);
		get_next_c(rules, sin_cos, next_c, 1);
	}
	else
	{
		get_next(rules, sin_cos, next, 0);
		get_next_c(rules, sin_cos, next_c, 0);
	}
	if (act[0] != next[0] || act[1] != next[1]
		|| !(our_modulo(next_c[0], (int)rules->map.block_width))
		|| !(our_modulo(next_c[1], (int)rules->map.block_width)))
		return (verify_collide(rules, next));
	return (0);
}
