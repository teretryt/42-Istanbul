/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturker <rturker@42istanbul.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:46:00 by rturker           #+#    #+#             */
/*   Updated: 2022/10/10 10:29:17 by rturker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *nw)
{
	if (!nw)
		return ;
	else if (!lst)
	{
		*lst = nw;
		return ;
	}	
	nw->next = *lst;
	*lst = nw;
}
