/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:11 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/15 17:25:45 by ddelladi         ###   ########.fr       */
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

void	find_enemy_pos(t_enemies **ptr, t_map *map, int i)
{
	int	occ;
	int	x;
	int	y;

	occ = 1;
	y = -1;
	while (++y < map->map_height_len[1])
	{
		x = -1;
		while (++x < map->map_height_len[0])
		{
			if (map->map[y][x] == '4' && occ == i)
			{
				(*ptr)->x = x;
				(*ptr)->y = y;
				return ;
			}
			else if (map->map[y][x] == '4')
				occ++;
		}
	}
}

void	load_enemies(t_rules *rules)
{
	int			n;
	int			i;
	t_enemies	**ptr;

	n = count_enemies(&rules->map);
	i = 0;
	ptr = &rules->enemies;
	while (i++ < n)
	{
		if (*ptr)
		{
			(*ptr)->next = malloc(sizeof(t_enemies));
			if (!(*ptr)->next)
				die("Malloc error");
			*ptr = (*ptr)->next;
		}
		else
		{
			*ptr = malloc(sizeof(t_enemies));
			if (!*ptr)
				die("Malloc error");
		}
		find_enemy_pos(ptr, &rules->map, i);
		(*ptr)->enemy_img.img = mlx_xpm_file_to_image(rules->mlx.mlx, "./img/enemies/ss_front.xpm", &(*ptr)->enemy_img.width, &(*ptr)->enemy_img.height);
		if (!(*ptr)->enemy_img.img)
			die("Error loading enemy image. Aborting");
		(*ptr)->next = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 2)
		die("Usage: ./cub3d [.cub file]");
	init_rules(&rules);
	init_window(&rules.mlx);
	read_file(argv[1], &rules);
	load_enemies(&rules);
	add_events(&rules);
	game(&rules);
	mlx_loop_hook(rules.mlx.mlx, loop_events, &rules);
	mlx_loop(rules.mlx.mlx);
	return (0);
}


/*

- pistola con immagine più grande
- animazioni porte
- pistola che spara
- nemici
- livello trama
- fov con mouse
- *importante* le textures scelte nella funzione choose_texture sono scambiate? Nel senso di west al posto di east, forse anche nord/sud. In caso è da cambiare anche nella mandatory!!!

*/
