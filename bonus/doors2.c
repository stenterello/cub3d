/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:51:17 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/23 13:50:28 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	try_open_door(t_rules *rules)
{
	if (in_front_of_door(rules)
		&& rules->n_frames - rules->last_door_action > 350)
		open_door(rules);
	else if (in_front_of_open_door(rules)
		&& rules->n_frames - rules->last_door_action > 350)
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
