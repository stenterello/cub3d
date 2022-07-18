/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_rules_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:42:37 by ddelladi          #+#    #+#             */
/*   Updated: 2022/07/18 13:05:41 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isascii(str[i]) || str[i] == ' ')
			return (0);
		i++;
	}
	if (str[i] == '\n')
		str[i] = '\0';
	return (1);
}

int	is_parameter(char *str)
{
	int	i;
	int	flag;
	int	n;

	i = 0;
	flag = 0;
	n = 0;
	while (str[i] && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) && !flag)
		{
			flag++;
			n++;
		}
		if (str[i] == ',' && !flag)
			return (0);
		if (str[i] == ',' && flag)
			flag--;
		i++;
	}
	if (n != 3)
		return (0);
	return (1);
}

static void	copy_into(char **dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] == ' ')
		i++;
	if (*dst)
		die("Rule defined multiple times");
	malloc_c(dst, ft_strlen(&src[i]) + 1);
	ft_strlcpy(*dst, &src[i], ft_strlen(&src[i]) + 1);
}

// static char	take_number(char *str, int *i)
// {
// 	int	ret;
// 	int	j;
	
// 	j = 0;
// 	ret = (char)ft_atoi(str);
// 	while (ft_isdigit(str[j]))
// 		j++;
// 	*i += j + 1;
// 	return (ret);
// }

static void	copy_rgb(int rgb[3], char *src)
{
	int		i;
	int	i2;
	int		n;

	i = 0;
	n = 0;
	i2 = 0;
	while (i < 3)
	{
		while (!ft_isdigit(src[i2]) || src[i2] == ' ')
			i2++;
		rgb[n++] = ft_atoi(&src[i2]);
		while (ft_isdigit(src[i2]))
			i2++;
		i++;
	}
}

void	insert_rule(char *rul, t_rules *rules)
{
	if (!ft_strncmp("NO", rul, 2))
		copy_into(&rules->north_texture_path, &rul[2]);
	else if (!ft_strncmp("SO", rul, 2))
		copy_into(&rules->south_texture_path, &rul[2]);
	else if (!ft_strncmp("EA", rul, 2))
		copy_into(&rules->east_texture_path, &rul[2]);
	else if (!ft_strncmp("WE", rul, 2))
		copy_into(&rules->west_texture_path, &rul[2]);
	else if (!ft_strncmp("F", rul, 1) && rules->floor_color[0] == INT_MAX)
		copy_rgb(rules->floor_color, &rul[1]);
	else if (!ft_strncmp("F", rul, 1) && rules->floor_color[0] != INT_MAX)
		die("Rule defined multiple times");
	else if (!ft_strncmp("C", rul, 1) && rules->ceiling_color[0] == INT_MAX)
		copy_rgb(rules->ceiling_color, &rul[1]);
	else if (!ft_strncmp("C", rul, 1) && rules->ceiling_color[0] != INT_MAX)
		die("Rule defined multiple times");
}
