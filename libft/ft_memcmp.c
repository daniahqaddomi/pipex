/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:57:22 by dqaddomi          #+#    #+#             */
/*   Updated: 2024/09/07 15:04:48 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)ptr1;
	p2 = (const unsigned char *)ptr2;
	i = 0;
	while (i < num)
	{
		if (p1[i] > p2[i])
		{
			return (1);
		}
		if (p1[i] < p2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
