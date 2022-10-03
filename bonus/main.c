/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:11 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/03 23:24:48 by ddelladi         ###   ########.fr       */
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

void	load_animations(t_rules *rules)
{
	rules->animations = malloc(sizeof(t_image *) * 4);
	if (!rules->animations)
		die("Malloc error");
	rules->animations[0] = malloc(sizeof(t_image));
	if (!rules->animations[0])
		die("Malloc error");
	rules->animations[0]->img = mlx_xpm_file_to_image(rules->mlx.mlx, ENEMY_TEX, &rules->animations[0]->width, &rules->animations[0]->height);
	rules->animations[0]->addr = mlx_get_data_addr(rules->animations[0]->img, &rules->animations[0]->bpp, &rules->animations[0]->line_length, &rules->animations[0]->endian);
	rules->animations[1] = malloc(sizeof(t_image));
	if (!rules->animations[1])
		die("Malloc error");
	rules->animations[1]->img = mlx_xpm_file_to_image(rules->mlx.mlx, AMMO_TEX, &rules->animations[1]->width, &rules->animations[1]->height);
	rules->animations[1]->addr = mlx_get_data_addr(rules->animations[1]->img, &rules->animations[1]->bpp, &rules->animations[1]->line_length, &rules->animations[1]->endian);
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
	load_animations(&rules);
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
- animazioni nemici
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
- aggiungere sprite dell'ammo storage
- cambiare il sort_spr in un t_sprite ** per fare tutti i puntatori e non copiare mai tutta la t_sprite
- aggiungere tutti i controlli di corretto caricamento dell'immagine da parte di minilibX

*/
