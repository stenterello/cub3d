/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:08:01 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/07 17:09:31 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	change_enemy_state(t_rules *rules)
{
	int			i;

	i = -1;
	while (++i < rules->n_sprites)
	{
		if (get_sprite_dist(rules, &rules->spr[i]) < rules->map.block_width
			&& rules->spr[i].type)
		{
			rules->spr[i].attacking = 3;
			rules->spr[i].type = 1;
		}
	}
}

void	move_straight_x(t_rules *rules, int res, int flag)
{
	if (!rules->player.gun.counted)
	{
		rules->player.gun.counter++;
		rules->player.gun.counted++;
	}
	if (!res || res == 3)
	{
		if (flag)
			rules->player.x += rules->player.d_x * rules->player.speed;
		else
			rules->player.x -= rules->player.d_x * rules->player.speed;
	}
	else if (res == 2 && !rules->player.earning_dmg)
	{
		if (flag)
			rules->player.x -= rules->player.d_x * rules->player.speed * 2;
		else
			rules->player.x += rules->player.d_x * rules->player.speed * 2;
		rules->player.health -= 5;
		rules->player.earning_dmg = 1;
		change_enemy_state(rules);
	}
	if (res == 3)
		rules->player.ammo += 5;
}

void	move_straight_y(t_rules *rules, int res, int flag)
{
	if (!rules->player.gun.counted)
	{
		rules->player.gun.counter++;
		rules->player.gun.counted++;
	}
	if (!res || res == 3)
	{
		if (flag)
			rules->player.y += rules->player.d_y * rules->player.speed;
		else
			rules->player.y -= rules->player.d_y * rules->player.speed;
	}
	else if (res == 2 && !rules->player.earning_dmg)
	{
		if (flag)
			rules->player.y -= rules->player.d_y * rules->player.speed * 2;
		else
			rules->player.y += rules->player.d_y * rules->player.speed * 2;
		rules->player.health -= 5;
		rules->player.earning_dmg = 1;
		change_enemy_state(rules);
	}
	if (res == 3)
		rules->player.ammo += 5;
}

void	move_lateral_x(t_rules *rules, int res, int flag)
{
	if (!rules->player.gun.counted)
	{
		rules->player.gun.counter++;
		rules->player.gun.counted++;
	}
	if (!res || res == 3)
	{
		if (flag)
			rules->player.x += rules->player.d_y * rules->player.speed;
		else
			rules->player.x -= rules->player.d_y * rules->player.speed;
	}
	else if (res == 2 && !rules->player.earning_dmg)
	{
		if (flag)
			rules->player.y -= rules->player.d_x * rules->player.speed * 2;
		else
			rules->player.y += rules->player.d_x * rules->player.speed * 2;
		rules->player.health -= 5;
		rules->player.earning_dmg = 1;
		change_enemy_state(rules);
	}
	if (res == 3)
		rules->player.ammo += 5;
}

void	move_lateral_y(t_rules *rules, int res, int flag)
{
	if (!rules->player.gun.counted)
	{
		rules->player.gun.counter++;
		rules->player.gun.counted++;
	}
	if (!res || res == 3)
	{
		if (flag)
			rules->player.y += rules->player.d_x * rules->player.speed;
		else
			rules->player.y -= rules->player.d_x * rules->player.speed;
	}
	else if (res == 2 && !rules->player.earning_dmg)
	{
		if (flag)
			rules->player.x -= rules->player.d_y * rules->player.speed * 2;
		else
			rules->player.x += rules->player.d_y * rules->player.speed * 2;
		rules->player.health -= 5;
		rules->player.earning_dmg = 1;
		change_enemy_state(rules);
	}
	if (res == 3)
		rules->player.ammo += 5;
}
