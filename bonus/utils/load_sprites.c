/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:20:58 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/03 23:49:10 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	clear_sprites(t_rules *rules, t_sprite *spr)
{
	int	i;

	i = -1;
	while (++i < rules->n_sprites)
	{
		spr[i].x = 0;
		spr[i].y = 0;
		spr[i].mini_x = 0;
		spr[i].mini_y = 0;
		spr[i].dist = 0;
		spr[i].state = 0;
		spr[i].type = -1;
	}
}

static void	sort_sprites(t_rules *rules)
{
	int	*sorted_index;

	sorted_index = find_indexes(rules);
	rules->sort_spr = malloc(sizeof(t_sprite) * (rules->n_sprites));
	if (!rules->sort_spr)
		die("Malloc error");
	fill_sort_spr(rules, sorted_index);
	free(sorted_index);
}

static void	save_sprites(t_rules *rules)
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
			if (rules->map.map[i][j] == '4' || rules->map.map[i][j] == '5')
			{
				rules->spr[ind].state = 1;
				rules->spr[ind].mini_x = j;
				rules->spr[ind].mini_y = i;
				if (rules->map.map[i][j] == '4')
					rules->spr[ind++].type = 0;
				else
					rules->spr[ind++].type = 1;
			}
			i++;
		}
	}
}

void	reload_sprites(t_rules *rules)
{
	clear_sprites(rules, rules->spr);
	clear_sprites(rules, rules->sort_spr);
	save_sprites(rules);
	free(rules->sort_spr);
	sort_sprites(rules);
}

void	load_sprites(t_rules *rules)
{
	rules->n_sprites = count_sprites(rules->map);
	rules->spr = malloc(sizeof(t_sprite) * (rules->n_sprites + 1));
	if (!rules->spr)
		die("Malloc error");
	clear_sprites(rules, rules->spr);
	save_sprites(rules);
	sort_sprites(rules);
}
