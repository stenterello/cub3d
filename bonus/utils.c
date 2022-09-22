/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:38:55 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/20 12:10:02 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	die(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int	get_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	take_rgb(char *str, unsigned char rgb[3])
{
	int	i;
	int	i2;
	int	tmp;

	i = 0;
	i2 = 0;
	while (str[i] && !ft_isdigit(str[i]))
	{
		i++;
		if (str[i] && ft_isdigit(str[i]))
		{
			tmp = ft_atoi(&str[i]);
			if (tmp > 255 || tmp < 0)
				die("Invalid color value. Aborting");
			rgb[i2++] = (unsigned char)tmp;
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
	}
	if (i2 != 3)
		die("RGB wrong format in .cub file");
	return (1);
}

void	init_rules_2(t_rules *rules)
{
	rules->map.map = NULL;
	rules->north = NULL;
	rules->east = NULL;
	rules->south = NULL;
	rules->west = NULL;
	rules->door = NULL;
	rules->floor = NULL;
	rules->ceiling = NULL;
	rules->line_offset = 0;
	rules->mlx.win_width = 1280;
	rules->mlx.win_height = 720;
}

void	init_rules(t_rules *rules)
{
	init_rules_2(rules);
	rules->keys.w_pressed = 0;
	rules->keys.a_pressed = 0;
	rules->keys.s_pressed = 0;
	rules->keys.d_pressed = 0;
	rules->keys.l_pressed = 0;
	rules->keys.r_pressed = 0;
	rules->keys.e_pressed = 0;
	rules->keys.shift_pressed = 0;
	rules->n_frames = 1;
	rules->line_offset = 0;
	rules->mouse.last_x = 0;
	rules->mouse.last_y = 0;
	rules->mouse.moved = 0;
	rules->last_door_action = 0;
	rules->player.gun.last_shoot = 0;
	rules->player.gun.path = malloc(sizeof(char) * (18));
	if (!rules->player.gun.path)
		die("Malloc error");
	ft_strlcpy(rules->player.gun.path, "./img/pistola.xpm", 18);
	rules->enemies = NULL;
}
