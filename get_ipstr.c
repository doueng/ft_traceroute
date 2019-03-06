/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ipstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:35:00 by dengstra          #+#    #+#             */
/*   Updated: 2019/03/06 16:35:01 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

char		*get_ipstr(char *ipstr, void *addr)
{
	ft_bzero(ipstr, INET_ADDRSTRLEN + 1);
	inet_ntop(AF_INET,
			addr,
			ipstr,
			INET_ADDRSTRLEN);
	return (ipstr);
}
