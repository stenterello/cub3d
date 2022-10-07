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

#include "cub3d_bonus.h"

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
	rules->player.plane = rules->player.dir + M_PI / 2;
	if (rules->player.dir == M_PI * 3 / 2)
		rules->player.plane = 0;
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

void	init_player_2(t_rules *r)
{
	r->player.healt.img = mlx_xpm_file_to_image(r->mlx.mlx,
			"./img/hud/hearth.xpm", &r->player.healt.width,
			&r->player.healt.height);
	if (!r->player.healt.img)
		die("Could not load textures. Aborting");
	r->player.healt.addr = mlx_get_data_addr(r->player.healt.img,
			&r->player.healt.bpp, &r->player.healt.line_length,
			&r->player.healt.endian);
	r->player.ammo_tex.img = mlx_xpm_file_to_image(r->mlx.mlx,
			"./img/hud/ammo.xpm", &r->player.ammo_tex.width,
			&r->player.ammo_tex.height);
	if (!r->player.ammo_tex.img)
		die("Could not load textures. Aborting");
	r->player.ammo_tex.addr = mlx_get_data_addr(r->player.ammo_tex.img,
			&r->player.ammo_tex.bpp, &r->player.ammo_tex.line_length,
			&r->player.ammo_tex.endian);
	r->player.viewfinder.img = mlx_xpm_file_to_image(r->mlx.mlx,
			"./img/hud/viewfinder.xpm", &r->player.viewfinder.width,
			&r->player.viewfinder.height);
	if (!r->player.viewfinder.img)
		die("Could not load textures. Aborting");
	r->player.viewfinder.addr = mlx_get_data_addr(r->player.viewfinder.img,
			&r->player.viewfinder.bpp, &r->player.viewfinder.line_length,
			&r->player.viewfinder.endian);
	r->player.earning_dmg = 0;
}

void	init_player(t_rules *r, char c, int i, int j)
{
	init_player_position(r, c, i, j);
	r->player.speed = SPEED;
	r->player.gun.off = 0;
	r->player.gun.counter = 0;
	r->player.plane_x = -cos(r->player.plane);
	r->player.plane_y = sin(r->player.plane);
	r->player.health = 100;
	r->player.ammo = 10;
	init_player_2(r);
}

void	init_keys(t_rules *rules)
{
	rules->keys.w_pressed = 0;
	rules->keys.a_pressed = 0;
	rules->keys.s_pressed = 0;
	rules->keys.d_pressed = 0;
	rules->keys.l_pressed = 0;
	rules->keys.r_pressed = 0;
	rules->keys.e_pressed = 0;
	rules->keys.shift_pressed = 0;
	rules->mouse.last_x = 0;
	rules->mouse.last_y = 0;
	rules->mouse.moved = 0;
}

void	init_rules(t_rules *rules)
{
	rules->game_status = PLAY;
	rules->map.map = NULL;
	rules->north = NULL;
	rules->east = NULL;
	rules->south = NULL;
	rules->west = NULL;
	rules->door = NULL;
	rules->floor = NULL;
	rules->ceiling = NULL;
	rules->line_offset = 0;
	rules->mlx.win_width = 854;
	rules->mlx.win_height = 480;
	rules->dist_array = malloc(sizeof(double) * (rules->mlx.win_width + 1));
	if (!rules->dist_array)
		die("Malloc error");
	init_keys(rules);
	rules->n_frames = 1;
	rules->line_offset = 0;
	rules->last_door_action = 0;
	rules->player.gun.last_shoot = 0;
	rules->player.gun.path = malloc(sizeof(char) * (22));
	if (!rules->player.gun.path)
		die("Malloc error");
	ft_strlcpy(rules->player.gun.path, "./img/gun/pistola.xpm", 22);
}
