/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:10:18 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 22:28:27 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	load_gun(t_rules *rules)
{
	t_image	*gun;

	gun = &rules->player.gun.gun_img;
	gun->img = mlx_xpm_file_to_image(rules->mlx.mlx, rules->player.gun.path, &gun->width, &gun->height);
	if (!gun->img)
		die("Could not load textures. Aborting");
	gun->addr = mlx_get_data_addr(gun->img, &gun->bpp, &gun->line_length, &gun->endian);
}

void	bullet(t_rules *rules)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, rules->player.d_x * rules->player.speed, 0, 1);
	res2 = colliding(rules, 0, rules->player.d_y * rules->player.speed, 1);
	if (res1 == 2 || res2 == 2)
		printf("ciao");
}

void	shoot(t_rules *rules)
{
	ft_strlcpy(rules->player.gun.path, "./img/gun/sparo.xpm", 20);
	rules->player.gun.last_shoot = rules->n_frames;
	mlx_destroy_image(rules->mlx.mlx, rules->player.gun.gun_img.img);
	load_gun(rules);
	bullet(rules);
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
