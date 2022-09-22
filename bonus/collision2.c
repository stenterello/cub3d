/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:26:20 by ddelladi          #+#    #+#             */
/*   Updated: 2022/09/20 11:48:36 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	get_next_plus(t_rules *rules, float r_cos, float r_sin, int next[2])
{
	next[0] = (rules->player.x + r_cos) / rules->map.block_width;
	next[1] = (rules->player.y + r_sin) / rules->map.block_width;
}

void	get_next_minus(t_rules *rules, float r_cos, float r_sin, int next[2])
{
	next[0] = (rules->player.x - r_cos) / rules->map.block_width;
	next[1] = (rules->player.y - r_sin) / rules->map.block_width;
}

void	get_next_c_plus(t_rules *rules, float r_cos, float r_sin, int next_c[2])
{
	next_c[0] = rules->player.x + r_cos;
	next_c[1] = rules->player.y + r_sin;
}

void	get_c_minus(t_rules *rules, float r_cos, float r_sin, int next_c[2])
{
	next_c[0] = rules->player.x - r_cos;
	next_c[1] = rules->player.y - r_sin;
}
