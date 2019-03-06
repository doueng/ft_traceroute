/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeaddr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:44:01 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/14 16:44:02 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	ft_freeaddrinfo(struct addrinfo *curr)
{
	struct addrinfo *tmp;

	while (curr)
	{
		tmp = curr->ai_next;
		free(curr->ai_addr);
		free(curr->ai_canonname);
		free(curr);
		curr = tmp;
	}
}
