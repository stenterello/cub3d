/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:40:23 by ddelladi          #+#    #+#             */
/*   Updated: 2022/06/22 13:45:16 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	usage(void)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("\nUsage:\n\t./cub3d file_to_read.cub", 2);
	exit(-1);
}

void	die(char *str)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit(-1);
}
