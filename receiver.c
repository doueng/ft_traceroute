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

void	receiver(t_env *env,
			struct ip *ip_recv,
			struct icmp *icmp_recv,
			struct timeval *recv_time)
{
	char				*buff;
	size_t				buffsize;

	buffsize = sizeof(*ip_recv) + sizeof(*icmp_recv);
	buff = xv(ft_memalloc(buffsize), MALLOC);
	errno = 0;
	recvfrom(env->recvsock, buff, buffsize, MSG_WAITALL, NULL, NULL);
	x(gettimeofday(recv_time, NULL), TIMEOFDAY);
	ft_memcpy(ip_recv, buff, sizeof(*ip_recv));
	ft_memcpy(icmp_recv, buff + sizeof(*ip_recv), sizeof(*icmp_recv));
	free(buff);
}
