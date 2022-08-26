/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:22:38 by ddelladi          #+#    #+#             */
/*   Updated: 2022/08/26 18:21:19 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	horizontal_checks(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((map[i][j] == '0' || ft_isalpha(map[i][j])) && (j == 0
				|| map[i][j + 1] == ' ' || map[i][j + 1] == '\n'
				|| map[i][j - 1] == ' '))
				return (0);
		}
	}
	return (1);
}

int	vertical_checks(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->map_height_len[0])
	{
		i = 0;
		while (map->map[i] && map->map[i][j])
		{
			if ((map->map[i][j] == '0' || ft_isalpha(map->map[i][j])) && (i == 0
				|| i == map->map_height_len[1] || map->map[i - 1][j] == ' '
				|| map->map[i + 1][j] == ' ' || map->map[i - 1][j] == '\n'
				|| map->map[i + 1][j] == '\n'))
				return (0);
			i++;
		}
	}
	return (1);
}

void	define_player(t_rules *rules, char c, int i, int j)
{
	if (c == 'N')
		rules->player.dir = M_PI / 2;
	else if (c == 'W')
		rules->player.dir = M_PI;
	else if (c == 'S')
		rules->player.dir = M_PI * 3 / 2;
	else if (c == 'E')
		rules->player.dir = 2 * M_PI;
	rules->map.map[i][j] = '0';
	rules->player.x = ++i * rules->map.block_width
		- (rules->map.block_width / 2);
	rules->player.y = ++j * rules->map.block_width
		- (rules->map.block_width / 2);
	printf("PLAYER INFO\n");
	printf("DIR: %f\n", rules->player.dir);
	printf("X: %f\n", rules->player.x);
	printf("Y: %f\n", rules->player.y);
}

int	find_player(t_rules *rules)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = -1;
	while (rules->map.map[++i])
	{
		j = -1;
		while (rules->map.map[i][++j])
		{
			if (rules->map.map[i][j] == 'N' || rules->map.map[i][j] == 'S'
				|| rules->map.map[i][j] == 'W' || rules->map.map[i][j] == 'E')
			{
				ret++;
				define_player(rules, rules->map.map[i][j], i, j);
			}
			else if (!ft_isdigit(rules->map.map[i][j]) && rules->map.map[i][j]
					!= '\n' && rules->map.map[i][j] != ' ')
				return (0);
			if (ret > 1)
				return (ret);
		}
	}
	return (ret);
}

void	map_checks(t_rules *rules)
{
	int	c;

	if (!horizontal_checks(rules->map.map) || !vertical_checks(&rules->map))
		die("Map is not closed. Aborting");
	c = find_player(rules);
	if (!c)
		die("There isn't a valid player in the map. Maybe some wrong \
			characters in the map? Check it and retry. Aborting");
	else if (c == 2)
		die("There must be only one player in the map. Aborting");
}
