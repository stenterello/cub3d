/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:36:34 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/22 14:58:38 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rules(t_rules *rules)
{
	rules->map = NULL;
	rules->north_texture_path = NULL;
	rules->south_texture_path = NULL;
	rules->east_texture_path = NULL;
	rules->west_texture_path = NULL;
	rules->win_width = 600;
	rules->win_height = 480;
	rules->mini_block_width = 20;
	rules->block_width = 250;
	rules->map_width = 0;
	rules->ceiling_color[0] = INT_MAX;
	rules->ceiling_color[1] = INT_MAX;
	rules->ceiling_color[2] = INT_MAX;
	rules->floor_color[0] = INT_MAX;
	rules->floor_color[1] = INT_MAX;
	rules->floor_color[2] = INT_MAX;
	rules->d_angle = PI / 2 / rules->win_width;
	rules->nframes = 0;
	rules->rate = 20;
	rules->w_pressed = 0;
	rules->a_pressed = 0;
	rules->s_pressed = 0;
	rules->d_pressed = 0;
	rules->l_pressed = 0;
	rules->r_pressed = 0;
}

void	free_rules(t_rules *rules)
{
	if (rules->north_texture_path)
		free(rules->north_texture_path);
	if (rules->south_texture_path)
		free(rules->south_texture_path);
	if (rules->east_texture_path)
		free(rules->east_texture_path);
	if (rules->west_texture_path)
		free(rules->west_texture_path);
}

void	update_pov(t_rules *rules)
{
	if (rules->w_pressed && !colliding(rules, "up"))
		rules->player.y -= rules->block_width / 10;
	if (!colliding(rules, "left") && rules->a_pressed)
		rules->player.x -= rules->block_width / 10;
	if (rules->s_pressed && !colliding(rules, "down"))
		rules->player.y += rules->block_width / 10;
	if (rules->d_pressed && !colliding(rules, "right"))
		rules->player.x += rules->block_width / 10;
	if (rules->l_pressed)
		rules->player.dir -= ANGLE_UNIT * 5;
	if (rules->r_pressed)
		rules->player.dir += ANGLE_UNIT * 5;
	if (rules->player.dir < 0)
		rules->player.dir = 2 * PI;
	if (rules->player.dir > 2 * PI)
		rules->player.dir = 0;
}

int	update_screen(t_rules *rules)
{
	if (rules->nframes % rules->rate == 0)
	{
		update_pov(rules);
		draw_view_rays(rules);
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
	mlx_loop_hook(rules.mlx, update_screen, &rules);
	mlx_loop(rules.mlx);
	free_rules(&rules);
	return (0);
}


/*

- quando si prendono i parametri all'inizio, verificare che i path forniti siano a file esistenti e per cui si possiedono permessi [ da implementare nel file ]
- print_map in check.c funzione solo di test, poi dovrà essere cancellata
- da fare:
	.check sulla mappa (funzione map_check(rules))
- il Makefile RELINKA!
- visione errata quando ci si attacca ai muri in alto e a sinistra!! (distanza dal muro = 0)

*/
