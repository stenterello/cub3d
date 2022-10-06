/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:30:26 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/06 17:19:27 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	change_enemy_state(t_rules *rules)
{
	int			i;

	i = -1;
	while (++i < rules->n_sprites)
	{
		if (get_sprite_dist(rules, &rules->spr[i]) < rules->map.block_width && rules->spr[i].type)
		{
			rules->spr[i].attacking = 3;
			rules->spr[i].type = 1;
		}
	}
}

static void	check_up(t_rules *rules, float ray_cos, float ray_sin)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, ray_cos, 0, 1);
	res2 = colliding(rules, 0, ray_sin, 1);
	if (res1 != 1)
	{
		if (!rules->player.gun.counted)
		{
			rules->player.gun.counter++;
			rules->player.gun.counted++;
		}
		if (!res1 || res1 == 3)
			rules->player.x += rules->player.d_x * rules->player.speed;
		else if (res1 == 2 && !rules->player.earning_dmg)
		{
			rules->player.x -= rules->player.d_x * rules->player.speed * 2;
			rules->player.health -= 5;
			rules->player.earning_dmg = 1;
			change_enemy_state(rules);
		}
		if (res1 == 3)
			rules->player.ammo += 10;
	}
	if (res2 != 1)
	{
		if (!rules->player.gun.counted)
		{
			rules->player.gun.counter++;
			rules->player.gun.counted++;
		}
		if (!res2 || res2 == 3)
			rules->player.y += rules->player.d_y * rules->player.speed;
		else if (res2 == 2 && !rules->player.earning_dmg)
		{
			rules->player.y -= rules->player.d_y * rules->player.speed * 2;
			rules->player.health -= 5;
			rules->player.earning_dmg = 1;
			change_enemy_state(rules);
		}
		if (res2 == 3)
			rules->player.ammo += 10;
	}
}

static void	check_down(t_rules *rules, float ray_cos, float ray_sin)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, ray_cos, 0, 0);
	res2 = colliding(rules, 0, ray_sin, 0);
	if (res1 != 1)
	{
		if (!rules->player.gun.counted)
		{
			rules->player.gun.counter++;
			rules->player.gun.counted++;
		}
		if (!res1 || res1 == 3)
			rules->player.x -= rules->player.d_x * rules->player.speed;
		else if (res1 == 2 && !rules->player.earning_dmg)
		{
			rules->player.x += rules->player.d_x * rules->player.speed * 2;
			rules->player.health -= 5;
			rules->player.earning_dmg = 1;
			change_enemy_state(rules);
		}
		if (res1 == 3)
			rules->player.ammo += 10;
	}
	if (res2 != 1)
	{
		if (!rules->player.gun.counted)
		{
			rules->player.gun.counter++;
			rules->player.gun.counted++;
		}
		if (!res2 || res2 == 3)
			rules->player.y -= rules->player.d_y * rules->player.speed;
		else if (res2 == 2 && !rules->player.earning_dmg)
		{
			rules->player.y += rules->player.d_y * rules->player.speed * 2;
			rules->player.health -= 5;
			rules->player.earning_dmg = 1;
			change_enemy_state(rules);
		}
		if (res2 == 3)
			rules->player.ammo += 10;
	}
}

static void	check_left(t_rules *rules, float ray_cos, float ray_sin)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, ray_sin, 0, 1);
	res2 = colliding(rules, 0, ray_cos, 0);
	if (res1 != 1)
	{
		if (!rules->player.gun.counted)
		{
			rules->player.gun.counter++;
			rules->player.gun.counted++;
		}
		if (!res1 || res1 == 3)
			rules->player.x += rules->player.d_y * rules->player.speed;
		else if (res1 == 2 && !rules->player.earning_dmg)
		{
			rules->player.x -= rules->player.d_y * rules->player.speed * 2;
			rules->player.health -= 5;
			rules->player.earning_dmg = 1;
			change_enemy_state(rules);
		}
		if (res1 == 3)
			rules->player.ammo += 10;
	}
	if (res2 != 2)
	{
		if (!rules->player.gun.counted)
		{
			rules->player.gun.counter++;
			rules->player.gun.counted++;
		}
		if (!res2 || res2 == 3)
			rules->player.y -= rules->player.d_x * rules->player.speed;
		else if (res2 == 2 && !rules->player.earning_dmg)
		{
			rules->player.y += rules->player.d_x * rules->player.speed * 2;
			rules->player.health -= 5;
			rules->player.earning_dmg = 1;
			change_enemy_state(rules);
		}
		if (res2 == 3)
			rules->player.ammo += 10;
	}
}

static void	check_right(t_rules *rules, float ray_cos, float ray_sin)
{
	int	res1;
	int	res2;

	res1 = colliding(rules, ray_sin, 0, 0);
	res2 = colliding(rules, 0, ray_cos, 1);
	if (res1 != 1)
	{
		if (!rules->player.gun.counted)
		{
			rules->player.gun.counter++;
			rules->player.gun.counted++;
		}
		if (!res1 || res1 == 3)
			rules->player.x -= rules->player.d_y * rules->player.speed;
		else if (res1 == 2 && !rules->player.earning_dmg)
		{
			rules->player.x += rules->player.d_y * rules->player.speed * 2;
			rules->player.health -= 5;
			rules->player.earning_dmg = 1;
			change_enemy_state(rules);
		}	
		if (res1 == 3)
			rules->player.ammo += 10;
	}
	if (res2 != 1)
	{
		if (!rules->player.gun.counted)
		{
			rules->player.gun.counter++;
			rules->player.gun.counted++;
		}
		if (!res2 || res2 == 3)
			rules->player.y += rules->player.d_x * rules->player.speed;
		else if (res2 == 2 && !rules->player.earning_dmg)
		{
			rules->player.y -= rules->player.d_x * rules->player.speed * 2;
			rules->player.health -= 5;
			rules->player.earning_dmg = 1;
			change_enemy_state(rules);
		}
		if (res2 == 3)
			rules->player.ammo += 10;
	}
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
	rules->player.earning_dmg = 0;
}
