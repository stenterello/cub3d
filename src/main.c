/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:36:34 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/27 11:10:51 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rules(t_rules *rules)
{
	rules->mlx.win_width = 600;
	rules->mlx.win_height = 480;
	rules->map.map = NULL;
	rules->map.mini_block = 20;
	rules->map.block = 250;
	rules->map.map_width = 0;
	rules->paths = malloc(sizeof(char *) * 5);
	if (!rules->paths)
		die("Malloc error");
	rules->ceiling_color[0] = INT_MAX;
	rules->ceiling_color[1] = INT_MAX;
	rules->ceiling_color[2] = INT_MAX;
	rules->floor_color[0] = INT_MAX;
	rules->floor_color[1] = INT_MAX;
	rules->floor_color[2] = INT_MAX;
	rules->d_angle = PI / 2 / rules->mlx.win_width;
	rules->nframes = 0;
	rules->rate = 20;
	rules->keys.w_pressed = 0;
	rules->keys.a_pressed = 0;
	rules->keys.s_pressed = 0;
	rules->keys.d_pressed = 0;
	rules->keys.l_pressed = 0;
	rules->keys.r_pressed = 0;
}

void	update_pov(t_rules *rules)
{
	if (rules->keys.w_pressed)
		move_player(rules, "up");
	if (rules->keys.a_pressed)
		move_player(rules, "left");
	if (rules->keys.s_pressed)
		move_player(rules, "down");
	if (rules->keys.d_pressed)
		move_player(rules, "right");
	if (rules->keys.l_pressed)
		rules->player.dir += ANGLE_UNIT * 5;
	if (rules->keys.r_pressed)
		rules->player.dir -= ANGLE_UNIT * 5;
	if (rules->player.dir < 0)
		rules->player.dir = 2 * PI;
	if (rules->player.dir > 2 * PI)
		rules->player.dir = 0;
	rules->player.d_x = cos(rules->player.dir);
	if (rules->player.dir == (double)PI)
		rules->player.d_y = 0;
	else
		rules->player.d_y = -sin(rules->player.dir);
}

int	update_screen(t_rules *rules)
{
	if (rules->nframes % rules->rate == 0)
	{
		update_pov(rules);
		game(rules);
	}
	rules->nframes++;
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	init_rules(&rules);
	input_check_and_rules_gen(argc, argv, &rules);
	init_window(&rules);
	game(&rules);
	add_events(&rules);
	mlx_loop_hook(rules.mlx.mlx, update_screen, &rules);
	mlx_loop(rules.mlx.mlx);
	free_rules(&rules);
	return (0);
}


/*

- da fare:
	.check sulla mappa (funzione map_check(rules))
	.non va in errore se non c'è il player nella mappa
- visione errata quando ci si attacca ai muri in alto e a sinistra!! (distanza dal muro = 0)
- il colore "None" dell'xpm attualmente viene processato come bianco
- rimane un bordo nero alla fine della texture
- rendere più visibile nello stdout <quale> texture sta creando problemi

*/
