/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus_map.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:55:31 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 13:11:36 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_MAP_H
# define CUB3D_BONUS_MAP_H

void	map_save(char *file, int fd, t_rules *rules);
void	map_checks(t_rules *rules);
void	get_measures(int fd, int hl[2]);
void	insert_rule(char *str, t_rules *rules);
int		is_map(char *line);

#endif
