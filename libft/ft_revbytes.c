/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revbytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:39:24 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/06 16:39:25 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t	ft_revbytes32(uint32_t bytes)
{
	return ((bytes << 24)
	| ((bytes << 8) & 0x00ff0000)
	| ((bytes >> 8) & 0x0000ff00)
	| (bytes >> 24));
}

uint16_t	ft_revbytes16(uint16_t bytes)
{
	return ((bytes << 8) | (bytes >> 8));
}
