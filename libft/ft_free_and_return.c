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

void	*ft_free_and_return(void *arg1, void *arg2, void *return_value)
{
	free(arg1);
	free(arg2);
	return (return_value);
}
