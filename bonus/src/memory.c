/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:08:51 by gimartin          #+#    #+#             */
/*   Updated: 2022/06/22 15:54:16 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_c(char **dst, int len)
{
	*dst = malloc(sizeof(char) * len);
	if (!*dst)
		die("Malloc error");
}

void	malloc_c_ptr(char ***dst, int len)
{
	*dst = malloc(sizeof(char *) * len);
	if (!*dst)
		die("Malloc error");
}
