/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:20:58 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/06 15:30:03 by ddelladi         ###   ########.fr       */
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
		spr[i].counter = 1;
		spr[i].type = -1;
	}
}

static void	sort_sprites(t_rules *rules)
{
	int	*sorted_index;

	sorted_index = find_indexes(rules);
	rules->sort_spr = malloc(sizeof(t_sprite *) * (rules->n_sprites));
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
				rules->spr[ind].counter = 1;
				rules->spr[ind].attacking = 0;
				rules->spr[ind].alive = 1;
				rules->spr[ind].dying = 0;
				if (rules->map.map[i][j] == '4')
					rules->spr[ind++].type = 1;
				else
					rules->spr[ind++].type = 0;
			}
			i++;
		}
	}
}

void	clear_sorted_sprites(t_rules *rules, t_sprite **sort_spr)
{
	int	i;

	i = -1;
	while (++i < rules->n_sprites)
		sort_spr[i] = NULL;
}

void	update_sprites(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_sprites)
	{
		rules->spr[i].dist = get_sprite_dist(rules, &rules->spr[i]);
		if (rules->spr[i].type && rules->spr[i].alive)
		{
			rules->spr[i].counter++;
			if (!(rules->spr[i].counter % 10) && rules->spr[i].type)
			{
				rules->spr[i].counter = 1;
				rules->spr[i].type++;
				if (rules->spr[i].type > 3)
				{
					rules->spr[i].type = 1;
					if (rules->spr[i].attacking)
						rules->spr[i].attacking = 0;
					if (rules->spr[i].dying)
					{
						rules->spr[i].alive = 0;
						rules->spr[i].type = 3;
					}
				}
			}
		}
	}
}

void	reload_sprites(t_rules *rules)
{
	update_sprites(rules);
	clear_sorted_sprites(rules, rules->sort_spr);
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
