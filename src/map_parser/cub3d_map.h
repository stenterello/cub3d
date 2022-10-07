/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CUB3D_map.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:55:31 by ddelladi          #+#    #+#             */
/*   Updated: 2022/10/01 13:36:02 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MAP_H
# define CUB3D_MAP_H

void	map_save(char *file, int fd, t_rules *rules);
void	map_checks(t_rules *rules);
void	take_rules(int fd, t_rules *rules);

#endif
