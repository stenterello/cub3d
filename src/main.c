/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:36:34 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/20 11:58:43 by ddelladi         ###   ########.fr       */
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
	rules->win_width = 800;
	rules->win_height = 600;
	rules->mini_block_width = 20;
	rules->block_width = 250;
	rules->map_width = 0;
	rules->ceiling_color[0] = INT_MAX;
	rules->ceiling_color[1] = INT_MAX;
	rules->ceiling_color[2] = INT_MAX;
	rules->floor_color[0] = INT_MAX;
	rules->floor_color[1] = INT_MAX;
	rules->floor_color[2] = INT_MAX;
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

int	main(int argc, char **argv)
{
	t_rules	rules;

	init_rules(&rules);
	input_check_and_rules_gen(argc, argv, &rules);
	init_window(&rules);
	minimap(&rules);
	add_events(&rules);
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

*/
