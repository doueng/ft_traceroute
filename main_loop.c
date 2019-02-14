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

static void		add_packet(struct timeval *send_time,
						struct timeval *recv_time)
{
	t_packet *packet;

	packet = xv(malloc(sizeof(*packet)), MALLOC);
	packet->triptime = recv_time->tv_usec - send_time->tv_usec;
	packet->next = g_env.packets;
	g_env.packets = packet;
}

static void		print_echoreply(struct ip *ip_recv,
								struct icmp *icmp_recv,
								struct timeval *send_time,
								struct timeval *recv_time)
{
	char src_addr[INET_ADDRSTRLEN + 1];

	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
		ip_recv->ip_len,
		get_ipstr(src_addr, &ip_recv->ip_src),
		icmp_recv->icmp_seq,
		ip_recv->ip_ttl,
		((recv_time->tv_usec - send_time->tv_usec) / 1000.0));
	if (ip_recv->ip_len != g_env.data_size + ICMP_SIZE)
		printf("wrong total length %d instead of %lu\n",
				ip_recv->ip_len,
				g_env.data_size + ICMP_SIZE);
}

static void		print_icmp(struct ip *ip_recv, struct icmp *icmp_recv)
{
	char src_addr[INET_ADDRSTRLEN + 1];

	g_env.options & V_OP
	? printf("%d bytes from %s: type = %d, code = %d\n",
		ip_recv->ip_len,
		get_ipstr(src_addr, &ip_recv->ip_src),
		icmp_recv->icmp_type,
		icmp_recv->icmp_code)
	: printf("Not an echo reply, enable the -v option to debug\n");
}

void			main_loop(void)
{
	struct timeval	send_time;
	struct timeval	recv_time;
	struct icmp		icmp_send;
	struct icmp		icmp_recv;
	struct ip		ip_recv;

	ft_bzero(&icmp_recv, sizeof(icmp_recv));
	gettimeofday(&send_time, NULL);
	sender(&icmp_send);
	if (receiver(&ip_recv, &icmp_recv))
	{
		gettimeofday(&recv_time, NULL);
		icmp_recv.icmp_type == ICMP_ECHOREPLY
		? print_echoreply(&ip_recv, &icmp_recv, &send_time, &recv_time)
		: print_icmp(&ip_recv, &icmp_recv);
		add_packet(&send_time, &recv_time);
	}
	alarm(1);
}
