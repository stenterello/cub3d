/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:35:11 by gimartin          #+#    #+#             */
/*   Updated: 2022/08/26 14:57:00 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	path_start(char *str)
{
	int	i;

	i = 2;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	take_rgb(char *str, int rgb[3])
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (str[i] && !ft_isdigit(str[i]))
	{
		i++;
		if (str[i] && ft_isdigit(str[i]))
		{
			rgb[i2++] = ft_atoi(&str[i]);
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
	}
	if (i2 != 3)
		die("RGB wrong format in .cub file");
	return (1);
}

void	read_file(char *file, t_rules *rules)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		die("Error opening file");
	take_rules(fd, rules);
	map_checks(file, fd, rules);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 2)
		die("Usage: ./cub3d [.cub file]");
	init_rules(&rules);
	read_file(argv[1], &rules);
	return (0);
}

/*

CHECKS:

- la mappa deve essere circondata da 1
- deve esserci la posizione del giocatore e deve essere NSWE

*/