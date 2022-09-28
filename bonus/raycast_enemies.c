/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:53:34 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/28 19:38:21 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	put_enemy_col(t_rules *rules, int x, int x_pxl, int l_h, t_image *enemy, int enemy_w)
{
	int		y;
	t_image	*tex;

	y = 0;
	tex = &rules->enemy;
	while (y < l_h)
	{
		easy_pxl(enemy, x, y, get_color(tex,
			x_pxl, our_modulo(y, l_h) * rules->enemy.height / enemy_w, rules));
		y++;
	}
}

void	draw_enemy(t_rules *rules, t_bres_data *data)
{
	t_enemy_info	en;

	ft_bzero(&en.enemy_width, 4);
	en.x_off = 0;
	en.end_angle = get_end_angle(rules, data->dir1, &en.enemy_width, &en.x_off, get_real_start_angle(data->dir1, data, rules));
	en.start_x = data->x;
	ft_bzero(&en.mini_coord, 8);
	get_enemy_mini_coord(rules, data, en.mini_coord);
	en.dist = get_enemy_dist(rules, en.mini_coord);
	en.l_h = rules->enemy.width * rules->mlx.win_height / en.dist;
	en.start_y = rules->mlx.win_height / 2 - en.l_h / 2;
	en.end = en.start_y + en.l_h;
	if (en.start_y < 0)
		en.start_y = 0;
	if (en.end > rules->mlx.win_height)
		en.end = rules->mlx.win_height;
	en.enemy.img = mlx_new_image(rules->mlx.mlx, en.enemy_width, en.l_h);
	en.enemy.addr = mlx_get_data_addr(en.enemy.img, &en.enemy.bpp, &en.enemy.line_length, &en.enemy.endian);
	en.x = 0;
	while (data->dir1 > en.end_angle && data->x < rules->mlx.win_width)
	{
		put_enemy_col(rules, en.x, our_modulo(en.x, en.enemy_width + en.x_off) * rules->enemy.width / (en.enemy_width + en.x_off), en.l_h, &en.enemy, en.enemy_width);
		data->dir1 = decrement_angle(data->dir1, 1);
		data->x++;
		en.x++;
	}
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, en.enemy.img, en.start_x, en.start_y);
}

void	raycast_enemies(t_rules *rules)
{
	t_bres_data	data;

	data.dir1 = increment_angle(rules->player.dir,
			rules->mlx.win_width / 4);
	data.x = 0;
	while (data.x++ < rules->mlx.win_width)
	{
		if (enemy_in_view(data.dir1, rules, data.xy2))
			draw_enemy(rules, &data);
		while (enemy_in_view(data.dir1, rules, data.xy2))
		{
			data.x++;
			data.dir1 = decrement_angle(data.dir1, 1);
		}
		data.dir1 = decrement_angle(data.dir1, 1);
	}
}
