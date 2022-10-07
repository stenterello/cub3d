/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:57:44 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 12:21:28 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	menu(t_rules *rules)
{
	(void)rules;
}

static void	lost_screen(t_rules *rules)
{
	t_image	view;

	init_img(rules, &view, rules->mlx.win_width, rules->mlx.win_height);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
	mlx_string_put(rules->mlx.mlx, rules->mlx.mlx_win, rules->mlx.win_width
		/ 2, rules->mlx.win_height / 2, 0x00FFFFFF, "YOU LOST");
}

static void	check_state(t_rules *rules)
{
	if (!rules->player.health)
		rules->game_status = LOST;
	if (!rules->player.ammo)
		mlx_string_put(rules->mlx.mlx, rules->mlx.mlx_win,
			rules->mlx.win_width - 105, 60, 0x00FF0000, "NO AMMO");
}

static void	game(t_rules *rules)
{
	t_image	view;
	t_image	minimap;

	init_img(rules, &view, rules->mlx.win_width, rules->mlx.win_height);
	init_img(rules, &minimap,
		rules->map.map_height_len[0] * rules->map.mini_block_width,
		rules->map.map_height_len[1] * rules->map.mini_block_width);
	minimap2d(rules, &minimap);
	raycast(rules, &view, &minimap);
	draw_sprites(rules, &view);
	draw_gun(rules, &view);
	hud(rules, &view);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, view.img, 0, 0);
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win,
		minimap.img, 0, 0);
	draw_ammo_amount(rules);
	check_state(rules);
}

void	decide_game(t_rules *rules)
{
	if (rules->game_status == START)
		menu(rules);
	else if (rules->game_status == PLAY)
		game(rules);
	else if (rules->game_status == LOST)
		lost_screen(rules);
}
