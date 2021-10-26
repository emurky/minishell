/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_return.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkombu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:22:26 by rkombu            #+#    #+#             */
/*   Updated: 2021/10/26 20:22:30 by rkombu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	*ft_free_and_return(int num_args, ...)
{
	va_list	ap;
	int		i;
	void	*ret;

	va_start(ap, num_args);
	i = 0;
	while (i++ < num_args)
		free(va_arg(ap, void *));
	ret = va_arg(ap, void *);
	va_end(ap);
	return (ret);
}
