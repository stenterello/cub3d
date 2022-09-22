/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:51:17 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/20 11:52:23 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	try_open_door(t_rules *rules)
{
	if (in_front_of_door(rules)
		&& rules->n_frames - rules->last_door_action > 5)
		open_door(rules);
	else if (in_front_of_open_door(rules)
		&& rules->n_frames - rules->last_door_action > 5)
		close_door(rules);
}

int	is_door(int x, int y, t_rules *rules)
{
	if (rules->map.map[y][x] == '2')
		return (1);
	return (0);
}

int	is_open_door(int x, int y, t_rules *rules)
{
	if (rules->map.map[y][x] == '3')
		return (1);
	return (0);
}
