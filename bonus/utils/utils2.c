/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:08:38 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 13:12:08 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	our_modulo(double x, double y)
{
	while (x >= y && y != 0)
	{
		x -= y;
	}
	return (x);
}

int	choose_x(t_draw_info *info, float ref, t_rules *rules)
{
	return (our_modulo(ref, rules->map.block_width) * info->tex->width
		/ rules->map.block_width);
}

int	choose_y(int var, t_draw_info *info)
{
	return ((var - info->off) * info->tex->width / info->l_h);
}

unsigned int	get_color(t_image *tex, int x, int y, t_rules *rules)
{
	if (!(x < 0 || x > rules->mlx.win_width - 1
			|| y < 0 || y > rules->mlx.win_height - 1))
	{
		return (*(unsigned int *)(tex->addr + (4 * (tex->width * y + x))));
	}
	return (0x0);
}

void	shoot(t_rules *rules)
{
	ft_strlcpy(rules->player.gun.path, "./img/sparo.xpm", 16);
	rules->player.gun.last_shoot = rules->n_frames;
	mlx_destroy_image(rules->mlx.mlx, rules->player.gun.gun_img.img);
	load_gun(rules);
}

void	init_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		die("Error initializing Minilibx. Aborting");
	mlx->mlx_win = mlx_new_window(mlx->mlx,
			mlx->win_width, mlx->win_height, "Cub3d");
}

void	load_gun(t_rules *rules)
{
	t_image	*gun;

	gun = &rules->player.gun.gun_img;
	gun->img = mlx_xpm_file_to_image(rules->mlx.mlx, rules->player.gun.path, &gun->width, &gun->height);
	gun->addr = mlx_get_data_addr(gun->img, &gun->bpp, &gun->line_length, &gun->endian);
}
