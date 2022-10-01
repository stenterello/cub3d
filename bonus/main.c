/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:11 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/01 13:11:55 by ddelladi         ###   ########.fr       */
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

int	count_enemies(t_map *map)
{
	int	ret;
	int	i;
	int	j;

	ret = 0;
	i = -1;
	while (++i < map->map_height_len[1])
	{
		j = -1;
		while (++j < map->map_height_len[0])
		{
			if (map->map[i][j] == '4')
				ret++;
		}
	}
	return (ret);
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
	game(&rules);
	mlx_loop_hook(rules.mlx.mlx, loop_events, &rules);
	mlx_loop(rules.mlx.mlx);
	return (0);
}


/*

- puntino rosso minimappa: nemico
- animazioni porte
- pistola che spara // CONTRO I NEMICI
- livello trama
- cambiare data->ray_angle in data->ray_angle per chiarezza
- togliere il raycast multiplo dalla versione mandatory!
- bloccare il cammino del player se incontra un nemico (dies)
- eliminare il terzo elemento di var[3] sia in mandatory che in bonus
- mettere la velocità della rotazione del player proporzionale alla grandezza
	dello schermo
- è possibile che nella funzione draw_sprite, il 2.6 non sia utilizzabile in tutte le risoluzioni
	(funzionante in 854x480)
- muovendo il pov con il mouse le sprite scompaiono!

*/
