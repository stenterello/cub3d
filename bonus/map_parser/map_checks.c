/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:22:38 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 12:11:03 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	isnt_a_wall(char map)
{
	if (map == '0' || map == '2' || map == '4' || map == '5')
		return (1);
	return (0);
}

static int	horizontal_checks(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((isnt_a_wall(map[i][j]) || ft_isalpha(map[i][j])) && (j == 0
				|| map[i][j + 1] == ' ' || map[i][j + 1] == '\n'
				|| map[i][j - 1] == ' '))
				return (0);
		}
	}
	return (1);
}

static int	vertical_checks(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->map_height_len[0])
	{
		i = 0;
		while (map->map[i] && map->map[i][j])
		{
			if ((isnt_a_wall(map->map[i][j]) || ft_isalpha(map->map[i][j]))
				&& (i == 0 || i == map->map_height_len[1] - 1
				|| map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
				|| map->map[i - 1][j] == '\n' || map->map[i + 1][j] == '\n'))
				return (0);
			i++;
		}
	}
	return (1);
}

static int	find_player(t_rules *rules)
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
				init_player(rules, rules->map.map[i][j], i, j);
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
		die("There isn't a valid player in the map. \n\
		\rMaybe some wrong characters in the map? Check it and retry. Aborting");
	else if (c > 1)
		die("There must be only one player in the map. Aborting");
}
