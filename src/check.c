/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:35:27 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/21 13:56:49 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_rules *rules)
{
	int	i;
	int	j;

	i = 0;
	while (rules->map[i])
	{
		j = 0;
		while (rules->map[i][j])
			ft_putchar_fd(rules->map[i][j++], 1);
		i++;
	}
}

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
	print_map(rules);
	close(fd);
}
