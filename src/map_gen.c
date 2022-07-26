/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:24:52 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 13:14:00 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	completed_rules(t_rules *rules)
{
	if (!rules->paths[0]
		|| !rules->paths[1]
		|| !rules->paths[2]
		|| !rules->paths[3]
		|| rules->floor_color[0] == INT_MAX
		|| rules->ceiling_color[0] == INT_MAX)
		return (0);
	return (1);
}

static int	not_a_right_parameter(char *str)
{
	int	i;

	i = 0;
	if (!ft_strncmp("NO", str, 2)
		|| !ft_strncmp("SO", str, 2)
		|| !ft_strncmp("WE", str, 2)
		|| !ft_strncmp("EA", str, 2))
	{
		i += 2;
		while (str[i] == ' ')
			i++;
		if (is_path(&str[i]))
			return (0);
	}
	else if (!ft_strncmp("F", str, 1)
		|| !ft_strncmp("C", str, 1))
	{
		i++;
		while (str[i] == ' ')
			i++;
		if (is_parameter(&str[i]))
			return (0);
	}
	return (1);
}

static int	not_a_rule(char *str)
{
	if (ft_strncmp("NO", str, 2)
		&& ft_strncmp("SO", str, 2)
		&& ft_strncmp("WE", str, 2)
		&& ft_strncmp("EA", str, 2)
		&& ft_strncmp("F", str, 1)
		&& ft_strncmp("C", str, 1))
		return (1);
	if (not_a_right_parameter(str))
		return (1);
	return (0);
}

static char	*take_rules(int fd, t_rules *rules)
{
	char	*tmp;
	char	*clean;

	tmp = get_next_line(fd);
	while (tmp && !completed_rules(rules))
	{
		if (ft_strncmp("\n", tmp, 1))
		{
			clean = ft_strtrim(tmp, " ");
			if (not_a_rule(clean))
				die("Map file is not regularly formatted");
			else
				insert_rule(clean, rules);
			free(clean);
		}
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (tmp);
}

void	generate_rules(int fd, t_rules *rules, char *file)
{
	char	*benchmark;

	benchmark = take_rules(fd, rules);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		die("Can't open file");
	skip_to_benchmark(fd, benchmark);
	rules->map.map_height = count_map_height_and_max_width(fd, rules);
	rules->map.map = malloc(sizeof(char *) * (rules->map.map_height-- + 1));
	if (!rules->map.map)
		die ("Malloc error");
	rules->map.map[0] = malloc(sizeof(char) * ft_strlen(benchmark) + 1);
	if (!rules->map.map[0])
		die("Malloc error");
	ft_strlcpy(rules->map.map[0], benchmark, ft_strlen(benchmark) + 1);
	check_player(benchmark, rules, 0);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		die("Can't open file");
	skip_to_benchmark(fd, benchmark);
	free(benchmark);
	define_map(fd, rules);
}
