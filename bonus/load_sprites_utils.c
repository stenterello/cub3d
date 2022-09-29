/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:21:53 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/29 22:43:27 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

double	final_length_double(double start_x, double start_y, double rxy[2])
{
	if (rxy[0] == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(get_abs(start_x - rxy[0]), 2) + pow(start_y - rxy[1], 2)));
}

int	count_sprites(t_map map)
{
	int	ret;
	int	i;
	int	j;

	ret = 0;
	j = -1;
	while (++j < map.map_height_len[0])
	{
		i = 0;
		while (map.map[i] && map.map[i][j])
		{
			if (map.map[i][j] == '4')
				ret++;
			i++;
		}
	}
	return (ret);
}

void	define_sprite(t_sprite *spr, int i, int j)
{
	spr->mini_x = j;
	spr->mini_y = i;
}

void	save_sprites(t_rules *rules)
{
	int	i;
	int	j;
	int	ind;

	j = -1;
	ind = 0;
	while (++j < rules->map.map_height_len[0])
	{
		i = 0;
		while (rules->map.map[i] && rules->map.map[i][j])
		{
			if (rules->map.map[i][j] == '4')
				define_sprite(&rules->spr[ind++], i, j);	
			i++;
		}
	}
}


