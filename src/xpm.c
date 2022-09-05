/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:28:39 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/04 13:30:42 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	find_color()
{

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
