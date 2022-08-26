/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:36:54 by gimartin          #+#    #+#             */
/*   Updated: 2022/08/26 14:58:01 by gimartin         ###   ########.fr       */
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
	{
		die("Missing rules in .cub file. Aborting");
	}
	free(tmp);
}

void	copy_rule(char *str, char **str2)
{
	if (*str2)
		die("Double rule definition in .cub file");
	*str2 = malloc(sizeof(char) * (ft_strlen(&str[path_start(str)])));
	if (!(*str2))
		die("Malloc error");
	ft_strlcpy((*str2), &str[path_start(str)],
		ft_strlen(&str[path_start(str)]));
}

void	insert_rule(char *str, t_rules *rules)
{
	if (!ft_strncmp(str, "NO", 2))
		copy_rule(str, &rules->north_path);
	else if (!ft_strncmp(str, "EA", 2))
		copy_rule(str, &rules->east_path);
	else if (!ft_strncmp(str, "SO", 2))
		copy_rule(str, &rules->south_path);
	else if (!ft_strncmp(str, "WE", 2))
		copy_rule(str, &rules->west_path);
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
