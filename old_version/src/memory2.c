/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:04:15 by ddelladi          #+#    #+#             */
/*   Updated: 2022/06/22 15:53:45 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array_of_array(char **arr)
{
	int	i;

	i = 0;
	if (arr[i])
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i++] = NULL;
		}
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}
