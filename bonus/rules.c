/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:36:54 by gimartin          #+#    #+#             */
/*   Updated: 2022/09/07 18:53:07 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	rules_completed(t_rules *rules)
{
	if (!rules->north || !rules->east || !rules->south
		|| !rules->west || !rules->floor || !rules->ceiling
		|| !rules->door)
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

t_image	*get_rule(char *str, t_rules *rules, t_image *chosen)
{
	char	*path;
	t_image	*ret;

	if (chosen)
		die("Double rule definition in .cub file. Aborting");
	path = get_path(str);
	ret = malloc(sizeof(t_image));
	if (!ret)
		die("Malloc error");
	ret->img = mlx_xpm_file_to_image(rules->mlx.mlx, path,
			&ret->width, &ret->height);
	if (!ret->img)
		die("Could not load textures. Aborting");
	ret->addr = mlx_get_data_addr(ret->img, &ret->bpp,
			&ret->line_length, &ret->endian);
	if (!ret)
		die("Could not load textures. Aborting");
	free(path);
	return (ret);
}

void	insert_rule(char *str, t_rules *rules)
{
	if (!ft_strncmp(str, "NO", 2))
		rules->north = get_rule(str, rules, rules->north);
	else if (!ft_strncmp(str, "EA", 2))
		rules->east = get_rule(str, rules, rules->east);
	else if (!ft_strncmp(str, "SO", 2))
		rules->south = get_rule(str, rules, rules->south);
	else if (!ft_strncmp(str, "WE", 2))
		rules->west = get_rule(str, rules, rules->west);
	else if (!ft_strncmp(str, "D", 1))
		rules->door = get_rule(str, rules, rules->door);
	else if (!ft_strncmp(str, "F", 1))
	{
		if (rules->floor)
			die("Double rule definition in .cub file. Aborting");
		rules->floor = take_rgb(str, rules->floor_color);
	}
	else if (!ft_strncmp(str, "C", 1))
	{
		if (rules->ceiling)
			die("Double rule definition in .cub file. Aborting");
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
