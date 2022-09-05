/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:36:54 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/05 13:57:13 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rules_completed(t_rules *rules)
{
	if (!rules->north_path || !rules->east_path || !rules->south_path
		|| !rules->west_path || !rules->floor || !rules->ceiling)
		return (0);
	return (1);
}

char	*get_path(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	ret = malloc(sizeof(char) * (ft_strlen(&str[i])));
	if (!ret)
		die("Malloc error");
	ft_strlcpy(ret, &str[i], (ft_strlen(&str[i])));
	return (ret);
}

void	copy_rule(char *str, t_image **image, t_rules *rules)
{
	char	*path;

	path = get_path(str);
	if (*(image))
		die("Double rule definition in .cub file");
	*image = malloc(sizeof(t_image *));
	if (!(*image))
		die("Malloc error");
	*image = mlx_xpm_file_to_image(rules->mlx.mlx, path,
			&(*image)->width, &(*image)->height);
	if (!(*image))
		die("Could not load textures. Aborting");
	free(path);
}

void	insert_rule(char *str, t_rules *rules)
{
	if (!ft_strncmp(str, "NO", 2))
		copy_rule(str, &rules->north, rules);
	else if (!ft_strncmp(str, "EA", 2))
		copy_rule(str, &rules->east, rules);
	else if (!ft_strncmp(str, "SO", 2))
		copy_rule(str, &rules->south, rules);
	else if (!ft_strncmp(str, "WE", 2))
		copy_rule(str, &rules->west, rules);
	else if (!ft_strncmp(str, "F", 1))
	{
		if (rules->floor)
			die("Double rule definition in .cub file");
		rules->floor = take_rgb(str, rules->floor_color);
	}
	else if (!ft_strncmp(str, "C", 1))
	{
		if (rules->ceiling)
			die("Double rule definition in .cub file");
		rules->ceiling = take_rgb(str, rules->ceiling_color);
	}
}

void	take_rules(int fd, t_rules *rules)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp && !rules_completed(rules))
	{
		rules->line_offset++;
		insert_rule(tmp, rules);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (!rules_completed(rules))
		die("Missing rules in .cub file. Aborting");
	free(tmp);
}
