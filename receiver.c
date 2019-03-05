/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:06 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:07 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

struct icmp	*receiver(t_env *env, struct ip *ip_recv, struct icmp *icmp_recv)
{
	char				buff[sizeof(struct ip) + sizeof(struct icmp)];
	size_t				buffsize;

	ft_bzero(icmp_recv, sizeof(icmp_recv));
	ft_bzero(ip_recv, sizeof(ip_recv));
	buffsize = sizeof(*ip_recv) + sizeof(*icmp_recv);
	recvfrom(env->sockfd, buff, buffsize, MSG_WAITALL, NULL, NULL);
	if (ft_revbytes16(icmp_recv->icmp_type != ICMP_ECHOREPLY))
		return (NULL);
	ft_memcpy(ip_recv, buff, sizeof(*ip_recv));
	ft_memcpy(icmp_recv, buff + sizeof(*ip_recv), sizeof(*icmp_recv));
	return (icmp_recv);
}
