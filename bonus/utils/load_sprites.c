/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:20:58 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 11:26:46 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	save_sprites_supp(t_rules *rules, int i, int ind, int j)
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
	return (ind);
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
			ind = save_sprites_supp(rules, i, ind, j);
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

void	update_supp(t_rules *rules, int i)
{
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
			update_supp(rules, i);
		}
	}
}
