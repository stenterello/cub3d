/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:38:55 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/02 16:09:06 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	path_start(char *str)
{
	int	i;

	i = 2;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	take_rgb(char *str, int rgb[3])
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (str[i] && !ft_isdigit(str[i]))
	{
		i++;
		if (str[i] && ft_isdigit(str[i]))
		{
			rgb[i2++] = ft_atoi(&str[i]);
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
	}
	if (i2 != 3)
		die("RGB wrong format in .cub file");
	return (1);
}

void	init_rules(t_rules *rules)
{
	rules->map.map = NULL;
	rules->north_path = NULL;
	rules->east_path = NULL;
	rules->south_path = NULL;
	rules->west_path = NULL;
	rules->floor = 0;
	rules->ceiling = 0;
	rules->line_offset = 0;
	rules->mlx.win_width = 1280;
	rules->mlx.win_height = 720;
	rules->keys.w_pressed = 0;
	rules->keys.a_pressed = 0;
	rules->keys.s_pressed = 0;
	rules->keys.d_pressed = 0;
	rules->keys.l_pressed = 0;
	rules->keys.r_pressed = 0;
	rules->n_frames = 0;
}

double	our_modulo(double x, double y)
{
	while (x >= y)
	{
		x -= y;
	}
	return (x);
}