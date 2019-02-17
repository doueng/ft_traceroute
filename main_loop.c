/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:00:02 by dengstra          #+#    #+#             */
/*   Updated: 2019/02/11 12:00:02 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static void		set_ttl(int sockfd, int ttl)
{
	x(setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl))
		, SETSOCK);
}

void			main_loop(t_env *env)
{
	struct icmp		icmp_send;
	struct icmp		icmp_recv;
	struct ip		ip_recv;
	char			src_addr[INET_ADDRSTRLEN + 1];
	int				ttl;

	ttl = 1;
	while (1)
	{
		set_ttl(env->sockfd, ttl);
		sender(env, &icmp_send);
		receiver(env, &ip_recv, &icmp_recv);
		printf("%2d\t%s\n", ttl, get_ipstr(src_addr, &ip_recv.ip_src));
		ttl++;
		if (ttl > env->maxhops || icmp_recv.icmp_type == ICMP_ECHOREPLY)
			break ;
	}
}
