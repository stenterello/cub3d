/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:11 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/01 20:36:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	read_file(char *file, t_rules *rules)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		die("Error opening file");
	take_rules(fd, rules);
	map_save(file, fd, rules);
	close(fd);
	rules->map.block_width = (rules->mlx.win_width
			/ (rules->map.map_height_len[0] - 1));
	rules->map.mini_block_width = rules->map.block_width / 4;
	map_checks(rules);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 2)
		die("Usage: ./cub3d [.cub file]");
	init_rules(&rules);
	init_window(&rules.mlx);
	load_gun(&rules);
	read_file(argv[1], &rules);
	load_sprites(&rules);
	load_gun(&rules);
	add_events(&rules);
	mlx_loop_hook(rules.mlx.mlx, loop_events, &rules);
	mlx_loop(rules.mlx.mlx);
	return (0);
}


/*

- animazioni porte
- pistola che spara // CONTRO I NEMICI
- livello trama
- togliere il raycast multiplo dalla versione mandatory!
- eliminare il terzo elemento di var[3] sia in mandatory che in bonus
- mettere la velocità della rotazione del player proporzionale alla grandezza
	dello schermo
- è possibile che nella funzione draw_sprite, il 2.6 non sia utilizzabile in tutte le risoluzioni
	(funzionante in 854x480)
- muovendo il pov con il mouse le sprite scompaiono!
- ordinare il codice mandatory in directories
- aggiustare il makefile che adesso compila i file oggetto soltanto col path del bonus project
- togliere la flag -g
- menu iniziale
- schermata di lost game
- aggiungere l'ammo storage

*/
