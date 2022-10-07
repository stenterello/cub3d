/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:38:55 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/01 14:07:48 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_position(t_rules *rules, char c, int i, int j)
{
	if (c == 'N')
		rules->player.dir = M_PI / 2;
	else if (c == 'W')
		rules->player.dir = M_PI;
	else if (c == 'S')
		rules->player.dir = M_PI * 3 / 2;
	else if (c == 'E')
		rules->player.dir = 0;
	rules->map.map[i][j] = '0';
	rules->player.x = ++j * rules->map.block_width
		- (rules->map.block_width / 2);
	rules->player.y = ++i * rules->map.block_width
		- (rules->map.block_width / 2);
	rules->player.d_x = cos(rules->player.dir);
	if (rules->player.dir == (double)M_PI)
		rules->player.d_y = 0;
	else
		rules->player.d_y = -sin(rules->player.dir);
}

void	init_player(t_rules *r, char c, int i, int j)
{
	init_player_position(r, c, i, j);
	r->player.speed = SPEED;
}

void	init_keys(t_rules *rules)
{
	rules->keys.w_pressed = 0;
	rules->keys.a_pressed = 0;
	rules->keys.s_pressed = 0;
	rules->keys.d_pressed = 0;
	rules->keys.l_pressed = 0;
	rules->keys.r_pressed = 0;
	rules->keys.shift_pressed = 0;
}

void	init_rules(t_rules *rules)
{
	rules->map.map = NULL;
	rules->north = NULL;
	rules->east = NULL;
	rules->south = NULL;
	rules->west = NULL;
	rules->floor = 0;
	rules->ceiling = 0;
	rules->line_offset = 0;
	rules->mlx.win_width = 1024;
	rules->mlx.win_height = 720;
	init_keys(rules);
	rules->n_frames = 1;
	rules->line_offset = 0;
}
