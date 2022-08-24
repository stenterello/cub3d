/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:08:51 by gimartin          #+#    #+#             */
/*   Updated: 2022/07/26 12:53:25 by ddelladi         ###   ########.fr       */
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

void	free_rules(t_rules *rules)
{
	if (rules->paths[0])
		free(rules->paths[0]);
	if (rules->paths[1])
		free(rules->paths[1]);
	if (rules->paths[2])
		free(rules->paths[2]);
	if (rules->paths[3])
		free(rules->paths[3]);
	if (rules->paths)
		free(rules->paths);
}
