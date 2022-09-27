/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:53:34 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/27 16:00:58 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	put_enemy_col(t_rules *rules, t_bres_data *data, int start, int end, int x_pxl, int l_h, t_image *enemy)
{
	int		y;
	t_image	*tex;

	y = start;
	tex = &rules->enemy;
	while (y < end)
	{
		easy_pxl(enemy, data->x, y, get_color(tex,
			x_pxl, (y - start) * tex->height / l_h, rules));
		y++;
	}
}


void	draw_enemy(t_rules *rules, t_bres_data *data)
{
	int		mini_coord[2];
	double	dist;
	int		l_h;
	int		start;
	int		end;
	double	start_angle;
	double	end_angle;
	t_image	enemy;
	int		enemy_width;
	int		start_x;

	ft_bzero(&enemy_width, 4);
	start_angle = data->dir1;
	start_x = data->x;
	end_angle = get_end_angle(rules, data->dir1, &enemy_width);
	ft_bzero(&mini_coord, 8);
	get_enemy_mini_coord(rules, data, mini_coord);
	dist = get_enemy_dist(rules, mini_coord);
	l_h = rules->enemy.width * rules->mlx.win_height / dist;
	start = rules->mlx.win_height / 2 - l_h / 2;
	end = start + l_h;
	if (start < 0)
		start = 0;
	if (end > rules->mlx.win_height)
		end = rules->mlx.win_height;
	enemy.img = mlx_new_image(rules->mlx.mlx, rules->mlx.win_width, rules->mlx.win_height);
	enemy.addr = mlx_get_data_addr(enemy.img, &enemy.bpp, &enemy.line_length, &enemy.endian);
	while (start_angle > end_angle)
	{
		put_enemy_col(rules, data, start, end, our_modulo((data->x - start_x), enemy_width) * rules->enemy.width / enemy_width, l_h, &enemy);
		start_angle = decrement_angle(start_angle, 1);
		data->x++;
	}
	mlx_put_image_to_window(rules->mlx.mlx, rules->mlx.mlx_win, enemy.img, 0, 0);
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
		// skip_enemy_block(rules, &data);
		while (enemy_in_view(data.dir1, rules, data.xy2))
		{
			data.x++;
			data.dir1 = decrement_angle(data.dir1, 1);
		}
		data.dir1 = decrement_angle(data.dir1, 1);
	}
}
