/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:18 by gimartin          #+#    #+#             */
/*   Updated: 2022/08/26 14:56:17 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_rules
{
	char		**map;
	char		*north_path;
	char		*east_path;
	char		*south_path;
	char		*west_path;
	int			floor_color[3];
	int			ceiling_color[3];
	int			floor;
	int			ceiling;
	int			line_offset;
}				t_rules;

void	map_checks(char *file, int fd, t_rules *rules);
void	init_rules(t_rules *rules);
int		path_start(char *str);
int		take_rgb(char *str, int rgb[3]);
void	read_file(char *file, t_rules *rules);
void	get_measures(int fd, int hl[2]);
void	print_map(char **map);
int		rules_completed(t_rules *rules);
void	take_rules(int fd, t_rules *rules);
void	copy_rule(char *str, char **str2);
void	insert_rule(char *str, t_rules *rules);
void	die(char *str);

#endif