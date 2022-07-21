/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:24:52 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 22:03:53 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	completed_rules(t_rules *rules)
{
	if (!rules->north_texture_path ||
		!rules->south_texture_path ||
		!rules->east_texture_path ||
		!rules->west_texture_path ||
		rules->floor_color[0] == INT_MAX ||
		rules->ceiling_color[0] == INT_MAX)
		return (0);
	return (1);
}

static int	not_a_right_parameter(char *str)
{
	int	i;

	i = 0;
	if (!ft_strncmp("NO", str, 2) ||
		!ft_strncmp("SO", str, 2) ||
		!ft_strncmp("WE", str, 2) ||
		!ft_strncmp("EA", str, 2))
		{
			i += 2;
			while (str[i] == ' ')
				i++;
			if (is_path(&str[i]))
				return (0);
		}
	else if (!ft_strncmp("F", str, 1) ||
		!ft_strncmp("C", str, 1))
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
	if (ft_strncmp("NO", str, 2) &&
		ft_strncmp("SO", str, 2) &&
		ft_strncmp("WE", str, 2) &&
		ft_strncmp("EA", str, 2) &&
		ft_strncmp("F", str, 1) &&
		ft_strncmp("C", str, 1))
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

void	skip_to_benchmark(int fd, char *benchmark)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp && ft_strncmp(tmp, benchmark, ft_strlen(benchmark)))
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (!ft_strncmp(tmp, benchmark, ft_strlen(benchmark)))
		free(tmp);
}

// int	check_map(t_rules *rules) // 0 è sbagliata, 1 è giusta
// {
// 	// int	i;
// 	// int	j;

// 	// i = 0;
// 	// horizontal check
// 	// while (rules->map[i])
// 	// {
// 	// 	j = 0;
// 	// 	while (rules->map[i][j])
// 	// 	{
			
// 	// 	}

// 	// }
// 	// vertical check
// 	return (1);
// }

void	generate_rules(int fd, t_rules *rules, char *file)
{
	char	*benchmark;

	benchmark = take_rules(fd, rules);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		die("Can't open file");
	skip_to_benchmark(fd, benchmark);
	rules->map_height = count_map_height_and_max_width(fd, rules);
	rules->map = malloc(sizeof(char *) * (rules->map_height + 1));
	if (!rules->map)
		die ("Malloc error");
	rules->map_height--;
	rules->map[0] = malloc(sizeof(char) * ft_strlen(benchmark) + 1);
	if (!rules->map[0])
		die("Malloc error");
	ft_strlcpy(rules->map[0], benchmark, ft_strlen(benchmark) + 1);
	check_player(benchmark, rules, 0);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		die("Can't open file");
	skip_to_benchmark(fd, benchmark);
	free(benchmark);
	define_map(fd, rules);
	define_texture(rules->west_texture_path, &rules->west_texture);
	define_texture(rules->north_texture_path, &rules->north_texture);
	// if (!check_map(rules))
	// 	die("Map error");
}
