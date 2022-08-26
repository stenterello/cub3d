/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:36:12 by gimartin          #+#    #+#             */
/*   Updated: 2022/08/26 14:38:34 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rules(t_rules *rules)
{
	rules->map = NULL;
	rules->north_path = NULL;
	rules->east_path = NULL;
	rules->south_path = NULL;
	rules->west_path = NULL;
	rules->floor = 0;
	rules->ceiling = 0;
	rules->line_offset = 0;
}
