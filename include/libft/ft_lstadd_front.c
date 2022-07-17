/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <ddelladi@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:28:23 by ddelladi          #+#    #+#             */
/*   Updated: 2022/06/22 14:38:24 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *next)
{
	if (!next)
		return ;
	if (!*lst)
		*lst = next;
	if (lst && next)
	{
		next->next = *lst;
		*lst = next;
	}
}
