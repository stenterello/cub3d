/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:39:54 by gimartin          #+#    #+#             */
/*   Updated: 2022/10/07 14:46:03 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	check_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != ' ' && line[i] != '\n'
			&& line[i] != '2' && line[i] != '4' && line[i] != '5')
			die("Not valid parameters in map. Aborting");
	}
}

static void	write_to_matrix(int i, t_rules *rules, char *tmp, int fd)
{
	int	j;

	while (i++ < rules->line_offset)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	i = 0;
	while (tmp)
	{
		j = ft_strlen(tmp);
		check_line(tmp);
		ft_strlcpy(rules->map.map[i], tmp, j-- + 1);
		while (j < rules->map.map_height_len[0])
			rules->map.map[i][j++] = ' ';
		rules->map.map[i][j++] = '\0';
		i++;
		free(tmp);
		tmp = get_next_line(fd);
	}
}

static void	get_measures(int fd, int hl[2])
{
	char	*tmp;

	hl[0] = 0;
	hl[1] = 1;
	tmp = get_next_line(fd);
	while (tmp)
	{
		if ((int)ft_strlen(tmp) > hl[0])
			hl[0] = ft_strlen(tmp);
		hl[1]++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
}

void	map_save(char *file, int fd, t_rules *rules)
{
	char	*tmp;
	int		i;

	ft_bzero(rules->map.map_height_len, 8);
	get_measures(fd, rules->map.map_height_len);
	rules->map.map = malloc(sizeof(char *)
			* (rules->map.map_height_len[1] + 1));
	if (!rules->map.map)
		die("Malloc error");
	i = 0;
	while (i < rules->map.map_height_len[1])
	{
		rules->map.map[i] = malloc(sizeof(char)
				* (rules->map.map_height_len[0] + 1));
		if (!rules->map.map[i++])
			die("Malloc error");
	}
	rules->map.map[i] = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		die("Error opening file");
	i = 0;
	tmp = get_next_line(fd);
	write_to_matrix(i, rules, tmp, fd);
}
