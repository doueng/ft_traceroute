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
	printf("%2d  ", ttl);
}

static double	get_triptime(struct timeval *send_time,
							struct timeval *recv_time)
{
	double			diff_ms;

	diff_ms = ((recv_time->tv_sec - send_time->tv_sec) * 1000.0)
		+ ((recv_time->tv_usec - send_time->tv_usec) / 1000.0);
	return (diff_ms);
}

static void		printer(uint32_t last_src_addr,
						uint32_t curr_src_addr,
						struct timeval *send_time,
						struct timeval *recv_time)
{
	char		ipstr[INET_ADDRSTRLEN + 1];

	if (errno == EAGAIN)
		printf(" * ");
	else
	{
		if (last_src_addr != curr_src_addr)
			printf(" %s ", get_ipstr(ipstr, &curr_src_addr));
		printf(" %.3f ms ", get_triptime(send_time, recv_time));
	}
}

static void		hopper(t_env *env,
						struct icmp *icmp_recv)
{
	int				num_fails;
	uint32_t		last_src_addr;
	struct ip		ip_recv;
	struct timeval	send_time;
	struct timeval	recv_time;

	num_fails = 0;
	last_src_addr = 0;
	while (num_fails++ < 3)
	{
		sender(env, &send_time);
		receiver(env, &ip_recv, icmp_recv, &recv_time);
		printer(last_src_addr,
				ip_recv.ip_src.s_addr,
				&send_time,
				&recv_time);
		last_src_addr = ip_recv.ip_src.s_addr;
	}
	printf("\n");
}

void			main_loop(t_env *env)
{
	struct icmp		icmp_recv;
	int				ttl;

	ttl = 1;
	while (1)
	{
		set_ttl(env->sendsock, ttl++);
		hopper(env, &icmp_recv);
		if (icmp_recv.icmp_type == ICMP_UNREACH_PORT || ttl >= env->maxhops)
			break ;
	}
}
