/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:53:34 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/28 00:01:27 by ddelladi         ###   ########.fr       */
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

double	get_real_start_angle(double angle, t_bres_data *data, t_rules *rules)
{
	int	coord[2];
	int	coord2[2];

	ft_bzero(&coord, 8);
	ft_bzero(&coord2, 8);
	get_enemy_mini_coord(rules, data, coord);
	get_enemy_mini_coord(rules, data, coord2);
	while (coord[0] == coord2[0] && coord[1] == coord2[1] && enemy_in_view(angle, rules, data->xy2))
	{
		angle = increment_angle(angle, 1);
		get_enemy_mini_coord(rules, data, coord2);
	}
	return (angle);
}

void	draw_enemy(t_rules *rules, t_bres_data *data, int flag)
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
	double	real_start;
	int		x_off;

	ft_bzero(&enemy_width, 4);
	start_angle = data->dir1;
	x_off = 0;
	if (!flag)
		real_start = get_real_start_angle(data->dir1, data, rules);
	else
		real_start = 0;
	end_angle = get_end_angle(rules, data->dir1, &enemy_width, &x_off, real_start);
	if (real_start)
		start_x = data->x + x_off;
	else
		start_x = data->x;
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
	while (start_angle > end_angle && data->x < rules->mlx.win_width)
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
	int			flag;

	flag = 0;
	data.dir1 = increment_angle(rules->player.dir,
			rules->mlx.win_width / 4);
	data.x = 0;
	while (data.x++ < rules->mlx.win_width)
	{
		if (enemy_in_view(data.dir1, rules, data.xy2))
			draw_enemy(rules, &data, flag);
		flag = 1;
		while (enemy_in_view(data.dir1, rules, data.xy2))
		{
			data.x++;
			data.dir1 = decrement_angle(data.dir1, 1);
		}
		data.dir1 = decrement_angle(data.dir1, 1);
	}
	(void)flag;
}
