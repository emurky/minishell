/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:25:48 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/09 21:25:52 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		if (lst->content)
			f(lst->content);
		lst = lst->next;
	}
}

void	ft_lstiter_with_arg(t_list *lst, void (*f)(void *, void *), void *arg)
{
	while (lst)
	{
		if (lst->content)
			f(lst->content, arg);
		lst = lst->next;
	}
}
