/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeaddr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:34:55 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/06 16:34:57 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	ft_freeaddrinfo(struct addrinfo *curr)
{
	struct addrinfo *tmp;

	while (curr)
	{
		tmp = curr->ai_next;
		free(curr->ai_canonname);
		free(curr);
		curr = tmp;
	}
}
