/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:24:47 by rkombu            #+#    #+#             */
/*   Updated: 2020/11/04 21:24:51 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb && (size > (size_t) - 1 / nmemb))
		return (NULL);
	size *= nmemb;
	p = malloc(size);
	if (!p)
		return (p);
	return (ft_memset(p, 0, size));
}
