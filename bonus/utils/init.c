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

void	init_player(t_rules *rules, char c, int i, int j)
{
	init_player_position(rules, c, i, j);
	rules->player.speed = SPEED;
	rules->player.gun.off = 0;
	rules->player.gun.counter = 0;
	rules->player.plane_x = -cos(rules->player.plane);
	rules->player.plane_y = sin(rules->player.plane);
	rules->player.health = 100;
	rules->player.ammo = 10;
	rules->player.heart_tex.img = mlx_xpm_file_to_image(rules->mlx.mlx, "./img/hud/hearth.xpm", &rules->player.heart_tex.width, &rules->player.heart_tex.height);
	if (!rules->player.heart_tex.img)
		die("Could not load textures. Aborting");
	rules->player.heart_tex.addr = mlx_get_data_addr(rules->player.heart_tex.img, &rules->player.heart_tex.bpp,
			&rules->player.heart_tex.line_length, &rules->player.heart_tex.endian);
	rules->player.ammo_tex.img = mlx_xpm_file_to_image(rules->mlx.mlx, "./img/hud/ammo.xpm", &rules->player.ammo_tex.width, &rules->player.ammo_tex.height);
	if (!rules->player.ammo_tex.img)
		die("Could not load textures. Aborting");
	rules->player.ammo_tex.addr = mlx_get_data_addr(rules->player.ammo_tex.img, &rules->player.ammo_tex.bpp,
			&rules->player.ammo_tex.line_length, &rules->player.ammo_tex.endian);
	rules->player.viewfinder.img = mlx_xpm_file_to_image(rules->mlx.mlx, "./img/hud/viewfinder.xpm", &rules->player.viewfinder.width, &rules->player.viewfinder.height);
	if (!rules->player.viewfinder.img)
		die("Could not load textures. Aborting");
	rules->player.viewfinder.addr = mlx_get_data_addr(rules->player.viewfinder.img, &rules->player.viewfinder.bpp,
			&rules->player.viewfinder.line_length, &rules->player.viewfinder.endian);
	rules->player.earning_dmg = 0;
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
