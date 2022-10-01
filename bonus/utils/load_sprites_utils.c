/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:21:53 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 14:04:42 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static double	get_sprite_dist(t_rules *rules, t_sprite *spr)
{
	double	spr_xy[2];

	spr_xy[0] = spr->mini_x * rules->map.block_width + rules->map.block_width / 2;
	spr_xy[1] = spr->mini_y * rules->map.block_width + rules->map.block_width / 2;
	spr->x = spr_xy[0];
	spr->y = spr_xy[1];
	return (final_length_double(rules->player.x, rules->player.y, spr_xy));
}

static void	move_one_forward(int *arr, int i, int limit)
{
	while (i > limit)
	{
		arr[i] = arr[i - 1];
		i--;
	}
}

int	*find_indexes(t_rules *rules)
{
	int		*ret;
	int		i;
	int		i2;

	ret = malloc(sizeof(int) * (rules->n_sprites + 1));
	if (!ret)
		die("Malloc error");
	i = 0;
	while (i < rules->n_sprites)
		ret[i++] = 0;
	i = 0;
	while (i < rules->n_sprites)
	{
		rules->spr[i].dist = get_sprite_dist(rules, &rules->spr[i]);
		i2 = 0;
		while (ret[i2] && rules->spr[i].dist < rules->spr[ret[i2] - 1].dist && i2 < rules->n_sprites)
			i2++;
		move_one_forward(ret, rules->n_sprites, i2);
		ret[i2] = i + 1;
		i++;
	}
	return (ret);
}

void	fill_sort_spr(t_rules *rules, int *arr)
{
	int	i;

	i = -1;
	while (++i < rules->n_sprites)
	{
		rules->sort_spr[i].x = rules->spr[arr[i] - 1].x;
		rules->sort_spr[i].y = rules->spr[arr[i] - 1].y;
		rules->sort_spr[i].mini_x = rules->spr[arr[i] - 1].mini_x;
		rules->sort_spr[i].mini_y = rules->spr[arr[i] - 1].mini_y;
		rules->sort_spr[i].dist = rules->spr[arr[i] - 1].dist;
	}
}
