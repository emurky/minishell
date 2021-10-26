/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:16:36 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/09 21:16:40 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*to_delete;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		to_delete = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(to_delete, del);
	}
	*lst = NULL;
}
