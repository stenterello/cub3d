/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:52:07 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/18 13:00:15 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	get_hex_color(int rgb[3])
{
	int	ret;

	ret = 0;
	ret = (int)rgb[0] * 256 * 256 + rgb[1] * 256 + rgb[2];
	return (ret);
}
