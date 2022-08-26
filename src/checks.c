/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:39:54 by gimartin          #+#    #+#             */
/*   Updated: 2022/08/26 15:00:30 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_map_checks(int i, t_rules *rules, char *tmp, int fd)
{
	while (i++ < rules->line_offset)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	i = 0;
	while (tmp)
	{
		ft_strlcpy(rules->map[i++], tmp, ft_strlen(tmp) + 1);
		free(tmp);
		tmp = get_next_line(fd);
	}
	print_map(rules->map);
}

void	map_checks(char *file, int fd, t_rules *rules)
{
	char	*tmp;
	int		measures[2];
	int		i;

	ft_bzero(&measures, 8);
	get_measures(fd, measures);
	rules->map = malloc(sizeof(char *) * (measures[1] + 1));
	if (!rules->map)
		die("Malloc error");
	i = 0;
	while (i < measures[1])
	{
		rules->map[i] = malloc(sizeof(char) * (measures[0] + 1));
		if (!rules->map[i++])
			die("Malloc error");
	}
	rules->map[i] = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		die("Error opening file");
	i = 0;
	tmp = get_next_line(fd);
	copy_map_checks(i, rules, tmp, fd);
}
