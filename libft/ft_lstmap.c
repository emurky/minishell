/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:29:28 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/09 21:29:30 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *, void *), void *arg)
{
	t_list	*new_lst;
	t_list	**curr;

	curr = &new_lst;
	while (lst)
	{
		*curr = ft_lstnew(NULL);
		if (!(*curr))
			return (NULL);
		if (lst->content)
			(*curr)->content = f(lst->content, arg);
		lst = lst->next;
		curr = &(*curr)->next;
	}
	return (new_lst);
}
