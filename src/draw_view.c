/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:28:36 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/03 19:22:09 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	phi(t_rules *rules, t_bres_data d)
{
	float	angle_diff;
	double	dist;

	dist = final_length(d.xy[0], d.xy[1], d.xy2);
	if (!dist)
		dist = 1;
	angle_diff = rules->player.dir - d.dir1;
	if (angle_diff < 0)
		angle_diff += (float)(2 * M_PI);
	else if (angle_diff > (float)(2 * M_PI))
		angle_diff -= 2 * M_PI;
	dist *= cos(angle_diff);
	return (dist);
}

void	adjust_var(int var[3], t_rules *rules)
{
	if (var[0] < 0)
		var[0] = 0;
	if (var[1] > rules->mlx.win_height)
		var[1] = rules->mlx.win_height;
	if (var[2] > rules->mlx.win_width)
		var[2] = rules->mlx.win_width;
}

t_xpm	*choose_texture(t_rules *rules)
{
	t_xpm	*ret;
	(void)rules;
	ret = 0;
	return (ret);
}

unsigned int	find_color(t_rules *rules, t_xpm *texture, int x, int y)
{
	t_couples		*act;
	int				r_x;
	int				r_y;
	char			*code;

	(void)rules;
	r_x = x % texture->size[0];
	if (r_x % 2)
		r_x += 1;
	if (r_x > texture->size[0] - 1)
		r_x -= 2;
	r_y = y % texture->size[0];
	code = malloc(sizeof(char) * (texture->char_n + 1));
	if (!code)
		die("Malloc error");
	if (r_y > texture->size[0] - 1)
		return (0x000000FF);
	if (r_y < 0)
		r_y = 0;
	ft_strlcpy(code, &texture->encoded[r_y][r_x], texture->char_n + 1);
	act = &texture->couples;
	while (act)
	{
		if (!ft_strncmp(act->key, code, texture->char_n))
			return (act->value);
		act = act->next;
	}
	return (0x0);
}

unsigned int	get_xpm_color(t_rules *rules, float dst[2], int y, double line_height, int off)
{
	// CAMBIARE GLI IF DI MODO CHE SCELGA LA TEXTURE CORRETTA
	unsigned int	ret;
	int		color_unit_x;

	if (!our_modulo(dst[0], rules->map.block_width) && (rules->player.dir < M_PI / 2 || rules->player.dir > 3 * M_PI / 2))
	{
		color_unit_x = rules->north.size[0] * round(((int)dst[1]
				% (int)rules->map.block_width)) / (int)rules->map.block_width;
		ret = find_color(rules, &rules->north, color_unit_x, (y - off) * rules->north.size[0] / line_height);
	}
	else if (!our_modulo(dst[0], rules->map.block_width) && rules->player.dir > M_PI / 2 && rules->player.dir < 3 * M_PI / 2)
	{
		color_unit_x = rules->north.size[0] * round(((int)dst[1]
				% (int)rules->map.block_width)) / (int)rules->map.block_width;
		ret = find_color(rules, &rules->north, color_unit_x, (y - off) * rules->north.size[0] / line_height);
	}
	else if (!our_modulo(dst[1], rules->map.block_width) && rules->player.dir > M_PI / 2 && rules->player.dir < 3 * M_PI / 2)
	{
		color_unit_x = rules->north.size[0] * round(((int)dst[0]
				% (int)rules->map.block_width)) / (int)rules->map.block_width;
		ret = find_color(rules, &rules->north, color_unit_x, (y - off) * rules->north.size[0] / line_height);
	}
	else
	{
		color_unit_x = rules->north.size[0] * round(((int)dst[0]
				% (int)rules->map.block_width)) / (int)rules->map.block_width;
		ret = find_color(rules, &rules->north, color_unit_x, (y - off) * rules->north.size[0] / line_height);
	}
	return (ret);
}

void	draw_view(t_bres_data d, t_image *view, t_rules *rules)
{
	double	line_height;
	double	dist;
	int		var[3];
	int		off;
	unsigned int	color;

	dist = phi(rules, d);
	line_height = rules->map.block_width * rules->mlx.win_height / dist;
	var[0] = rules->mlx.win_height / 2 - line_height / 2;
	var[1] = line_height + var[0];
	var[2] = d.x + (rules->mlx.win_width / 725 + 1);
	off = var[0];
	adjust_var(var, rules);
	while (d.x < var[2])
	{
		var[0] = rules->mlx.win_height / 2 - line_height / 2;
		if (var[0] < 0)
			var[0] = 0;
		else if (var[0] > rules->mlx.win_height)
			var[0] = rules->mlx.win_height;
		while (var[0] < var[1])
		{
			color = get_xpm_color(rules, d.xy2, var[0], line_height, off);
			easy_pxl(view, d.x, var[0], color);
			var[0]++;
		}
		d.x++;
	}
}
