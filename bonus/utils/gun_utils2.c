/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:42:11 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/07 18:08:02 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	bullet(t_rules *rules, double angle)
{
	float	f_pts[3];
	float	s_pts[3];

	horizontal_lines_check_enemy(angle, rules, f_pts);
	vertical_lines_check_enemy(angle, rules, s_pts);
	if (f_pts[0] && f_pts[0] > 0 && f_pts[0] / rules->map.block_width
		< rules->map.map_height_len[0]
		&& f_pts[1] > 0 && f_pts[1] / rules->map.block_width
		< rules->map.map_height_len[1])
		return (kill_enemy(rules, f_pts));
	else if (s_pts[0] && s_pts[0] > 0 && s_pts[0] / rules->map.block_width
		< rules->map.map_height_len[0]
		&& s_pts[1] > 0 && s_pts[1] / rules->map.block_width
		< rules->map.map_height_len[1])
		return (kill_enemy(rules, s_pts));
	return (0);
}

void	shoot(t_rules *rules)
{
	double	angle;
	int		i;

	i = 0;
	angle = increment_angle(rules->player.dir, 36);
	ft_strlcpy(rules->player.gun.path, "./img/gun/sparo.xpm", 20);
	rules->player.gun.last_shoot = rules->n_frames;
	mlx_destroy_image(rules->mlx.mlx, rules->player.gun.gun_img.img);
	load_gun(rules);
	while (i++ < 72)
	{
		if (bullet(rules, angle))
			return ;
		angle = decrement_angle(angle, 1);
	}
	rules->player.ammo -= 1;
}

void	restore_gun(t_rules *rules)
{
	if (!ft_strncmp(rules->player.gun.path, "./img/gun/sparo.xpm", 20)
		&& rules->n_frames - rules->player.gun.last_shoot > 350)
	{
		ft_strlcpy(rules->player.gun.path, "./img/gun/pistola.xpm", 22);
		mlx_destroy_image(rules->mlx.mlx, rules->player.gun.gun_img.img);
		load_gun(rules);
	}
}

void	move_gun(t_gun *gun, int i)
{
	if (gun->counter >= i)
	{
		if (gun->off)
			gun->off = 0;
		else
			gun->off = 10;
		gun->counter = 0;
	}
}
