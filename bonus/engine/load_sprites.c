/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:20:58 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 12:53:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	get_sprite_dist(t_rules *rules, t_sprite *spr)
{
	double	spr_xy[2];

	spr_xy[0] = spr->mini_x * rules->map.block_width + rules->map.block_width / 2;
	spr_xy[1] = spr->mini_y * rules->map.block_width + rules->map.block_width / 2;
	spr->x = spr_xy[0];
	spr->y = spr_xy[1];
	return (final_length_double(rules->player.x, rules->player.y, spr_xy));
}

void	move_one_forward(int *arr, int i, int limit)
{
	while (i > limit)
	{
		arr[i] = arr[i - 1];
		i--;
	}
}

void	clear_array(int *arr, int size, int n)
{
	int	i;

	i = 0;
	while (i < size)
		arr[i++] = n;
}

int	*find_indexes(t_rules *rules)
{
	int		*ret;
	int		i;
	int		i2;

	ret = malloc(sizeof(int) * (rules->n_sprites + 1));
	if (!ret)
		die("Malloc error");
	clear_array(ret, rules->n_sprites, 0);
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

void	sort_sprites(t_rules *rules)
{
	int	*sorted_index;

	sorted_index = find_indexes(rules);
	rules->sort_spr = malloc(sizeof(t_sprite) * (rules->n_sprites));
	if (!rules->sort_spr)
		die("Malloc error");
	fill_sort_spr(rules, sorted_index);
	free(sorted_index);
}

void	check(t_rules *rules)
{
	int	i;
	int	n_sprites;

	i = -1;
	n_sprites = count_sprites(rules->map);
	printf("***********NORMAL SPRITES***********\n");
	while (++i < n_sprites)
		printf("x: %f\ny: %f\nmini_x: %d\nmini_y: %d\ndist: %f\n\n", rules->spr[i].x, rules->spr[i].y, rules->spr[i].mini_x, rules->spr[i].mini_y, rules->spr[i].dist);
	i = -1;
	n_sprites = count_sprites(rules->map);
	printf("***********SORTED SPRITES***********\n");
	while (++i < n_sprites)
		printf("x: %f\ny: %f\nmini_x: %d\nmini_y: %d\ndist: %f\n\n", rules->sort_spr[i].x, rules->sort_spr[i].y, rules->sort_spr[i].mini_x, rules->sort_spr[i].mini_y, rules->sort_spr[i].dist);
}

void	clear_sprites(t_rules *rules, t_sprite *spr)
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
	rules->enemy.img = mlx_xpm_file_to_image(rules->mlx.mlx, "./img/enemies/ss_front2.xpm", &rules->enemy.width, &rules->enemy.height);
	if (!rules->enemy.img)
		die("Error loading texture. Aborting");
	rules->enemy.addr = mlx_get_data_addr(rules->enemy.img, &rules->enemy.bpp, &rules->enemy.line_length, &rules->enemy.endian);
	rules->n_sprites = count_sprites(rules->map);
	rules->spr = malloc(sizeof(t_sprite) * (rules->n_sprites + 1));
	if (!rules->spr)
		die("Malloc error");
	clear_sprites(rules, rules->spr);
	save_sprites(rules);
	sort_sprites(rules);
	//check(rules);
}
