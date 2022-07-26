/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:13:13 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/26 13:08:19 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	encode_rgb(u_int8_t alpha, u_int8_t red, u_int8_t green, u_int8_t blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}
