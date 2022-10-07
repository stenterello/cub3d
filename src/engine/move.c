/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:30:26 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 15:16:28 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_up(t_rules *rules, float ray_cos, float ray_sin)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, ray_cos, 0, 1);
	res2 = colliding(rules, 0, ray_sin, 1);
	if (!res1)
		rules->player.x += rules->player.d_x * rules->player.speed;
	if (!res2)
		rules->player.y += rules->player.d_y * rules->player.speed;
}

static void	check_down(t_rules *rules, float ray_cos, float ray_sin)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, ray_cos, 0, 0);
	res2 = colliding(rules, 0, ray_sin, 0);
	if (!res1)
		rules->player.x -= rules->player.d_x * rules->player.speed;
	if (!res2)
		rules->player.y -= rules->player.d_y * rules->player.speed;
}

static void	check_left(t_rules *rules, float ray_cos, float ray_sin)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, ray_sin, 0, 1);
	res2 = colliding(rules, 0, ray_cos, 0);
	if (!res1)
		rules->player.x += rules->player.d_y * rules->player.speed;
	if (!res2)
		rules->player.y -= rules->player.d_x * rules->player.speed;
}

static void	check_right(t_rules *rules, float ray_cos, float ray_sin)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, ray_sin, 0, 0);
	res2 = colliding(rules, 0, ray_cos, 1);
	if (!res1)
		rules->player.x -= rules->player.d_y * rules->player.speed;
	if (!res2)
		rules->player.y += rules->player.d_x * rules->player.speed;
}

void	move_player(t_rules *rules, char *dir)
{
	float	ray_cos;
	float	ray_sin;

	ray_cos = rules->player.d_x * rules->player.speed;
	ray_sin = rules->player.d_y * rules->player.speed;
	if (!ft_strncmp("up", dir, 2))
		check_up(rules, ray_cos, ray_sin);
	else if (!ft_strncmp("down", dir, 4))
		check_down(rules, ray_cos, ray_sin);
	else if (!ft_strncmp("left", dir, 4))
		check_left(rules, ray_cos, ray_sin);
	else if (!ft_strncmp("right", dir, 5))
		check_right(rules, ray_cos, ray_sin);
}