/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:41:34 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/01 13:35:51 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_map(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != ' ' && line[i] != '\n'
			&& line[i] != '2')
			return (0);
	}
	return (1);
}

static int	rules_completed(t_rules *rules)
{
	if (!rules->north || !rules->east || !rules->south
		|| !rules->west || !rules->floor || !rules->ceiling)
		return (0);
	return (1);
}

static void	insert_rule(char *str, t_rules *rules)
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
		rules->floor = get_rule(str, rules, rules->floor);
	else if (!ft_strncmp(str, "C", 1))
		rules->ceiling = get_rule(str, rules, rules->ceiling);
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
	while (!is_map(tmp))
	{
		rules->line_offset++;
		insert_rule(tmp, rules);
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
}
