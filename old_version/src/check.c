/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:35:27 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 14:44:13 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	input_check_and_rules_gen(int argc, char **argv, t_rules *rules)
{
	int	fd;

	if (argc != 2)
		usage();
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub\0", 4))
		die("File to read must have .cub extension");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		die("Can't open file");
	generate_rules(fd, rules, argv[1]);
	close(fd);
}

int	count_map_height_and_max_width(int fd, t_rules *rules)
{
	char	*tmp;
	int		count;

	count = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		if ((int)ft_strlen(tmp) - 1 > rules->map.map_width)
			rules->map.map_width = ft_strlen(tmp) - 1;
		free(tmp);
		count++;
		tmp = get_next_line(fd);
	}
	return (count);
}

void	check_player(char *tmp, t_rules *rules, int y)
{
	if (ft_strchr(tmp, 'N') != NULL
		|| ft_strchr(tmp, 'S') != NULL
		|| ft_strchr(tmp, 'W') != NULL
		|| ft_strchr(tmp, 'E') != NULL)
		define_player(tmp, rules, y);
	return ;
}
